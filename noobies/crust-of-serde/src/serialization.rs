use serde::{
    Serialize,
    ser::{SerializeStructVariant, SerializeTupleVariant},
};

use crate::E;

// What's the purpose of Serialize trait?
// Serialize trait defines behavior of serialization for a particular type given some Serializer.
// The serialize method takes &self, and map it into Serde data model by invoking exactly one of
// the methods on the given Serializer.
impl Serialize for E {
    fn serialize<S>(&self, serializer: S) -> Result<S::Ok, S::Error>
    where
        S: serde::Serializer,
    {
        const NAME: &'static str = "E";
        match self {
            Self::Color { r, g, b } => {
                let mut color = serializer.serialize_struct_variant(NAME, 0, "Color", 3)?;
                color.serialize_field("r", r)?;
                color.serialize_field("g", g)?;
                color.serialize_field("b", b)?;
                color.end()
            }
            Self::Point2D(x, y) => {
                let mut point = serializer.serialize_tuple_variant(NAME, 1, "Point2D", 2)?;
                point.serialize_field(x)?;
                point.serialize_field(y)?;
                point.end()
            }
            Self::Inches(n) => serializer.serialize_newtype_variant(NAME, 2, "Inches", n),
            Self::Instance => serializer.serialize_unit_variant(NAME, 3, "Instance"),
        }
    }
}
