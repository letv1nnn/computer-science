use serde::{Deserialize, Serialize};

#[derive(Debug, Serialize, Deserialize)]
struct Per {
    // rename, changes the serialized/deserialized name.
    #[serde(rename = "username")]
    first_name: String,
}

#[derive(Debug, Serialize, Deserialize)]
// rename_all, renames all fields
#[serde(rename_all = "camelCase")]
struct Foo {
    first_name: String,
    last_login_time: u64,
}

#[derive(Debug, Serialize, Deserialize)]
struct Bar {
    username: String,
    // skip ignores field completely
    // splits into skip_serializing and skip_deserializing
    #[serde(skip)]
    password_hash: String,
}

#[derive(Debug, Serialize, Deserialize)]
struct Config {
    // if value is missing, serde calls T.default()
    #[serde(default)]
    timeout: u64,
}

#[derive(Debug, Serialize, Deserialize)]
struct Usr {
    name: String,
    // serialize conditionally
    #[serde(skip_serializing_if = "Option::is_none")]
    age: Option<i32>,
}

#[derive(Debug, Serialize, Deserialize)]
struct Cons {
    name: String,
    // merge nested structs.
    #[serde(flatten)]
    addr: Address,
}

#[derive(Debug, Serialize, Deserialize)]
struct Address {
    city: String,
}

#[derive(Debug, Serialize, Deserialize)]
struct Kar {
    #[serde(alias = "username")]
    name: String
}

trait MyTrait: Serialize {}

#[derive(Serialize)]
#[serde(bound(serialize = "T: MyTrait"))]
struct Wrapper<T> {
    value:T
}
