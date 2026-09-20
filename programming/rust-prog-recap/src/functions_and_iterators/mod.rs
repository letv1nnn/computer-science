// 4. Функции и Итераторы. Программирование на Rust

#[test]
fn find_clang() {
    const LATEST: usize = 21;
    let clangs: [String; 7] =
        std::array::from_fn(|i| "clang-".to_string() + &format!("{}", LATEST - i));

    let clang_resource_dir: Option<String> = clangs.into_iter().find_map(|c| {
        if std::process::Command::new(&c)
            .arg("--version")
            .output()
            .is_ok()
        {
            std::process::Command::new(c)
                .arg("-print-resource-dir")
                .output()
                .ok()
                .filter(|o| o.status.success())
                .map(|o| String::from_utf8_lossy(&o.stdout).trim().to_string())
        } else {
            None
        }
    });

    assert_eq!(clang_resource_dir, None);
}
