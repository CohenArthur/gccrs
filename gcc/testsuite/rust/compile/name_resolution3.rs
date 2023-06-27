const BAR: u32 = {
    let ret = outer();

    const fn outer() -> u32 {
        0
    }

    ret
};
