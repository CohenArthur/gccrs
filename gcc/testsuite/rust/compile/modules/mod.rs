pub fn external_function() {
    let unused = 15; // { dg-warning "unused name" "" }
}

pub fn return_12() -> i32 {
    12
}
