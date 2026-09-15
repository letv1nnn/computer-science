/// Describes the purpose of an IPv4 address.
#[derive(Debug, Clone, Copy, PartialEq, Eq)]
pub(crate) enum IpV4Purpose {
    /// Identifies the local network, addresses whose first octet is 0.
    ThisNetwork,
    /// Identifies a single network interface.
    Unicast,
    /// Identifies a group of network interfaces.
    Multicast,
    /// Identifies all hosts on a network.
    Broadcast,
    /// Identifies the local host, the 127.0.0.0/8 range is reserved for this.
    Loopback,
    /// Reserved for future or experimental use, associated with Class E addresses.
    Reserved,
}

/// Describes IPv4 classes.
#[derive(Debug, Clone, Copy, PartialEq, Eq)]
pub(crate) enum IpV4Class {
    A,
    B,
    C,
    D,
    E,
}

/// describes ipv4 address
#[derive(Debug, Clone, Copy, PartialEq, Eq)]
pub(crate) struct IpV4Addr {
    addr: [u8; 4_usize],
    class: IpV4Class,
    purpose: IpV4Purpose,
}

impl IpV4Addr {
    pub(crate) const fn new(addr: [u8; 4_usize]) -> Self {
        Self {
            addr,
            class: Self::class_of(&addr),
            purpose: Self::purpose_of(&addr),
        }
    }

    pub(crate) const fn class_of(addr: &[u8; 4_usize]) -> IpV4Class {
        match addr[0] {
            0..=127 => IpV4Class::A,
            128..=191 => IpV4Class::B,
            192..=223 => IpV4Class::C,
            224..=239 => IpV4Class::D,
            240.. => IpV4Class::E,
        }
    }

    pub(crate) const fn purpose_of(addr: &[u8; 4_usize]) -> IpV4Purpose {
        match addr[0] {
            0 => IpV4Purpose::ThisNetwork,
            1..=126 | 128..=191 | 192..=223 => IpV4Purpose::Unicast,
            127 => IpV4Purpose::Loopback,
            224..=239 => IpV4Purpose::Multicast,
            240.. => IpV4Purpose::Reserved,
        }
    }

    pub(crate) const fn addr(&self) -> [u8; 4_usize] {
        self.addr
    }

    pub(crate) const fn class(&self) -> IpV4Class {
        self.class
    }

    pub(crate) const fn purpose(&self) -> IpV4Purpose {
        self.purpose
    }

    pub(crate) fn subnet_mask(ipv4: &IpV4Addr) -> Result<[u8; 4_usize], String> {
        let (class, purpose) = (ipv4.class, ipv4.purpose);
        match class {
            IpV4Class::A if matches!(purpose, IpV4Purpose::Unicast | IpV4Purpose::Loopback) => {
                Ok([255, 0, 0, 0])
            }
            IpV4Class::B => Ok([255, 255, 0, 0]),
            IpV4Class::C => Ok([255, 255, 255, 0]),
            other => Err(format!("no subnet mask for class {:?}", other).into()),
        }
    }

    pub(crate) fn network(ipv4: &IpV4Addr) -> Result<[u8; 4_usize], String> {
        let mask = Self::subnet_mask(ipv4)?;
        Ok(std::array::from_fn(|i| ipv4.addr[i] & mask[i]))
    }

    pub(crate) fn broadcast(ipv4: &IpV4Addr) -> Result<[u8; 4_usize], String> {
        let mask = Self::subnet_mask(ipv4)?;
        Ok(std::array::from_fn(|i| ipv4.addr[i] | !mask[i]))
    }

    pub(crate) fn netid<'a>(ipv4: &'a IpV4Addr) -> Result<&'a [u8], String> {
        let (class, purpose) = (ipv4.class, ipv4.purpose);
        match class {
            IpV4Class::A if matches!(purpose, IpV4Purpose::Unicast | IpV4Purpose::Loopback) => {
                Ok(&ipv4.addr[..=1])
            }
            IpV4Class::B => Ok(&ipv4.addr[..=2]),
            IpV4Class::C => Ok(&ipv4.addr[..=3]),
            other => Err(format!("no subnet mask for class {:?}", other).into()),
        }
    }

    pub(crate) fn hostid<'a>(ipv4: &'a IpV4Addr) -> Result<&'a [u8], String> {
        let (class, purpose) = (ipv4.class, ipv4.purpose);
        match class {
            IpV4Class::A if matches!(purpose, IpV4Purpose::Unicast | IpV4Purpose::Loopback) => {
                Ok(&ipv4.addr[1..])
            }
            IpV4Class::B => Ok(&ipv4.addr[2..]),
            IpV4Class::C => Ok(&ipv4.addr[3..]),
            other => Err(format!("no subnet mask for class {:?}", other).into()),
        }
    }

    pub(crate) fn number_of_hosts<'a>(ipv4: &'a IpV4Addr) -> Result<u32, String> {
        let host = Self::hostid(ipv4)?;
        Ok(2_u32.pow(host.len() as u32 * 8) - 2_u32)
    }
}

impl std::fmt::Display for IpV4Addr {
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        write!(
            f,
            "{}.{}.{}.{}",
            self.addr[0], self.addr[1], self.addr[2], self.addr[3]
        )
    }
}

impl TryFrom<String> for IpV4Addr {
    type Error = Box<dyn std::error::Error>;

    fn try_from(value: String) -> Result<Self, Self::Error> {
        let addr: [u8; 4_usize] = value
            .split(".")
            .map(|s| s.parse::<u8>())
            .collect::<Result<Vec<_>, _>>()?
            .try_into()
            .map_err(|_| "expected exactly 4 elements")?;

        Ok(Self::new(addr))
    }
}

impl<T> TryFrom<Vec<T>> for IpV4Addr
where
    T: Into<u8> + Copy + Clone,
{
    type Error = String;

    fn try_from(value: Vec<T>) -> Result<Self, Self::Error> {
        if value.len() != 4_usize {
            return Err(format!(
                "length of the given vector is not 4, actual length: {}",
                value.len()
            )
            .into());
        }
        let addr: [u8; 4_usize] = std::array::from_fn(|i| value[i].into());
        Ok(Self::new(addr))
    }
}

impl From<[u8; 4_usize]> for IpV4Addr {
    fn from(value: [u8; 4_usize]) -> Self {
        IpV4Addr::new(value)
    }
}

#[cfg(test)]
mod net_tests {
    use super::*;

    const ADDR: [u8; 4_usize] = [6, 97, 212, 211];

    #[test]
    fn ipv4_creation() {
        let ipv4 = IpV4Addr::new(ADDR);
        assert_eq!(ipv4.addr(), ADDR);
        assert_eq!(ipv4.class(), IpV4Class::A);
        assert_eq!(ipv4.purpose(), IpV4Purpose::Unicast);

        let ipv4_from: IpV4Addr = ADDR.into();
        assert_eq!(ipv4, ipv4_from);
    }

    #[test]
    fn ipv4_subnet_mask_network_and_broadcast() {
        let ipv4 = IpV4Addr::new(ADDR);

        let subnet_mask = IpV4Addr::subnet_mask(&ipv4).unwrap();
        assert_eq!(subnet_mask, [255, 0, 0, 0]);

        let network_addr = IpV4Addr::network(&ipv4).unwrap();
        assert_eq!(network_addr, [6, 0, 0, 0]);

        let broadcast_addr = IpV4Addr::broadcast(&ipv4).unwrap();
        assert_eq!(broadcast_addr, [6, 255, 255, 255]);
    }

    #[test]
    fn netid_hostid_and_number_of_possible_hosts() {
        let ipv4 = IpV4Addr::new(ADDR);

        let netid = IpV4Addr::netid(&ipv4).unwrap();
        assert_eq!(netid, &ipv4.addr()[..=1]);

        let hostid = IpV4Addr::hostid(&ipv4).unwrap();
        assert_eq!(hostid, &ipv4.addr()[1..]);

        let number_of_hosts = IpV4Addr::number_of_hosts(&ipv4).unwrap();
        assert_eq!(number_of_hosts, 2_u32.pow(24) - 2);
    }
}
