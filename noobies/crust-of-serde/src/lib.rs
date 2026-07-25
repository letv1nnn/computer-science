#![warn(missing_debug_implementations, rust_2018_idioms)]
#![allow(unused)]

mod attributes;
mod deserialization;
mod serialization;

use std::unimplemented;

#[derive(Debug, PartialEq)]
pub enum E {
    // Use three-step process:
    //   1. serialize_struct_variant
    //   2. serialize_field
    //   3. end
    Color { r: u8, g: u8, b: u8 },
    // Use three-step process:
    //   1. serialize_tuple_variant
    //   2. serialize_field
    //   3. end
    Point2D(f64, f64),
    // Use serialize_newtype_variant.
    Inches(u64),
    // Use serialize_unit_variant.
    Instance,
}

#[cfg(test)]
mod enum_serde_trait_impls_tests {
    use super::*;
    use serde_test::{Token, assert_tokens};

    const NAME: &'static str = "E";

    #[test]
    fn test_serde_instance() {
        let e_instance = E::Instance;

        assert_tokens(
            &e_instance,
            &[Token::UnitVariant {
                name: NAME,
                variant: "Instance",
            }],
        );
    }

    #[test]
    fn test_serde_inches() {
        let e_inches = E::Inches(42);

        assert_tokens(
            &e_inches,
            &[
                Token::NewtypeVariant {
                    name: NAME,
                    variant: "Inches",
                },
                Token::U64(42),
            ],
        );
    }

    #[test]
    fn test_serde_point2d() {
        let e_point2d = E::Point2D(-3.0, 3.0);

        assert_tokens(
            &e_point2d,
            &[
                Token::TupleVariant {
                    name: NAME,
                    variant: "Point2D",
                    len: 2,
                },
                Token::F64(-3.0),
                Token::F64(3.0),
                Token::TupleVariantEnd,
            ],
        );
    }

    #[test]
    fn test_serde_color() {
        let e_color = E::Color {
            r: 76,
            g: 33,
            b: 189,
        };

        assert_tokens(
            &e_color,
            &[
                Token::StructVariant {
                    name: NAME,
                    variant: "Color",
                    len: 3,
                },
                Token::Str("r"),
                Token::U8(76),
                Token::Str("g"),
                Token::U8(33),
                Token::Str("b"),
                Token::U8(189),
                Token::StructVariantEnd,
            ],
        );
    }
}
