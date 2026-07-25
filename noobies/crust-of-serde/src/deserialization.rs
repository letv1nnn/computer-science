use std::unimplemented;

use crate::{E, deserialization::Variant::Point2D};

use serde::{
    Deserialize,
    de::{self, VariantAccess, Visitor},
};

// What's the purpose of Deserialize trait?
// deserialize method takes some Deserializer and maps the type into Serde data model.
// WTF is the visitor?? Deserializer does not know what the sequence of data represents.
// Thus, it says, "give me a Visitor that knows how to build an E, and I'll drive it".
impl<'de> Deserialize<'de> for E {
    fn deserialize<D>(deserializer: D) -> Result<Self, D::Error>
    where
        D: serde::Deserializer<'de>,
    {
        const VARIANTS: &'static [&'static str] = &["Color", "Point2D", "Inches", "Instance"];

        // This is the only responsibility of Deserialize: tell the deserializer
        // what kind of value is expected and provide the appropriate visitor.
        deserializer.deserialize_enum("E", VARIANTS, EVisitor)
    }
}

#[derive(Debug)]
// A Visitor contains the logic for constructing a Rust value from Serde's data model.
struct EVisitor;

// Given that shape of data, here is how to build my Rust value
impl<'de> Visitor<'de> for EVisitor {
    type Value = E;

    fn expecting(&self, formatter: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        formatter.write_str("enum E")
    }

    // The deserializer will call this method after recognizing that the input represents an enum.
    fn visit_enum<A>(self, data: A) -> Result<Self::Value, A::Error>
    where
        A: serde::de::EnumAccess<'de>,
    {
        // variant identifies which enum variant was found.
        // access provides access to that variant's payload.
        let (variant, access) = data.variant::<Variant>()?;

        match variant {
            Variant::Instance => {
                access.unit_variant()?;
                Ok(E::Instance)
            }
            Variant::Inches => {
                let value = access.newtype_variant()?;
                Ok(E::Inches(value))
            }
            Variant::Point2D => access.tuple_variant(2, Point2DVisitor),
            Variant::Color => {
                const FIELDS: &'static [&'static str] = &["r", "g", "b"];
                access.struct_variant(FIELDS, ColorVisitor)
            }
        }
    }
}

#[derive(Debug)]
enum Variant {
    Color,
    Point2D,
    Inches,
    Instance,
}

impl<'de> Deserialize<'de> for Variant {
    fn deserialize<D>(deserializer: D) -> Result<Self, D::Error>
    where
        D: serde::Deserializer<'de>,
    {
        struct VariantVisitor;

        impl<'de> Visitor<'de> for VariantVisitor {
            type Value = Variant;

            fn expecting(&self, formatter: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
                formatter.write_str("variant of enum E")
            }

            fn visit_str<E>(self, v: &str) -> Result<Self::Value, E>
            where
                E: serde::de::Error,
            {
                match v {
                    "Color" => Ok(Variant::Color),
                    "Point2D" => Ok(Variant::Point2D),
                    "Inches" => Ok(Variant::Inches),
                    "Instance" => Ok(Variant::Instance),
                    _ => Err(de::Error::unknown_variant(
                        v,
                        &["Color", "Point2D", "Inches", "Instance"],
                    )),
                }
            }
        }

        deserializer.deserialize_identifier(VariantVisitor)
    }
}

#[derive(Debug)]
struct Point2DVisitor;

impl<'de> Visitor<'de> for Point2DVisitor {
    type Value = E;

    fn expecting(&self, formatter: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        formatter.write_str("typle variant Point2D")
    }

    fn visit_seq<A>(self, mut seq: A) -> Result<Self::Value, A::Error>
    where
        A: de::SeqAccess<'de>,
    {
        let x: f64 = seq
            .next_element()?
            .ok_or_else(|| de::Error::invalid_length(0, &self))?;

        let y: f64 = seq
            .next_element()?
            .ok_or_else(|| de::Error::invalid_length(1, &self))?;

        Ok(E::Point2D(x, y))
    }
}

#[derive(Debug)]
struct ColorVisitor;

impl<'de> Visitor<'de> for ColorVisitor {
    type Value = E;

    fn expecting(&self, formatter: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        formatter.write_str("struct variant Color")
    }

    fn visit_map<A>(self, mut map: A) -> Result<Self::Value, A::Error>
    where
        A: de::MapAccess<'de>,
    {
        let (mut r, mut g, mut b) = (None, None, None);

        while let Some(key) = map.next_key::<String>()? {
            match key.as_str() {
                "r" => r = Some(map.next_value()?),
                "g" => g = Some(map.next_value()?),
                "b" => b = Some(map.next_value()?),
                _ => {
                    let _: de::IgnoredAny = map.next_value()?;
                }
            }
        }

        Ok(E::Color {
            r: r.ok_or_else(|| de::Error::missing_field("r"))?,
            g: g.ok_or_else(|| de::Error::missing_field("g"))?,
            b: b.ok_or_else(|| de::Error::missing_field("b"))?,
        })
    }
}
