```diff
failures:

---- [ui (polonius)] ui/closures/closure-expected-type/expect-region-supply-region-2.rs stdout ----
diff of stderr:

29	...
30	LL |     closure_expecting_bound(|x: &'x u32| {
31	   |                              ^ requires that `'x` must outlive `'static`
-	   |
-	   = help: consider replacing `'x` with `'static`
34	
35	error: aborting due to 3 previous errors
36	


The actual stderr differed from the expected stderr.
Actual stderr saved to /home/arthur/Git/rust/build/x86_64-unknown-linux-gnu/test/ui/closures/closure-expected-type/expect-region-supply-region-2.polonius/expect-region-supply-region-2.polonius.stderr
To update references, rerun the tests and pass the `--bless` flag
To only update this specific test, also pass `--test-args closures/closure-expected-type/expect-region-supply-region-2.rs`

error: 1 errors occurred comparing output.
status: exit status: 1
command: "/home/arthur/Git/rust/build/x86_64-unknown-linux-gnu/stage1/bin/rustc" "/home/arthur/Git/rust/src/test/ui/closures/closure-expected-type/expect-region-supply-region-2.rs" "-Zthreads=1" "--target=x86_64-unknown-linux-gnu" "--error-format" "json" "--json" "future-incompat" "-Ccodegen-units=1" "-Zui-testing" "-Zdeduplicate-diagnostics=no" "--emit" "metadata" "-C" "prefer-dynamic" "--out-dir" "/home/arthur/Git/rust/build/x86_64-unknown-linux-gnu/test/ui/closures/closure-expected-type/expect-region-supply-region-2.polonius" "-Zpolonius" "-Zborrowck=mir" "-A" "unused" "-Crpath" "-O" "-Cdebuginfo=0" "-Lnative=/home/arthur/Git/rust/build/x86_64-unknown-linux-gnu/native/rust-test-helpers" "-L" "/home/arthur/Git/rust/build/x86_64-unknown-linux-gnu/test/ui/closures/closure-expected-type/expect-region-supply-region-2.polonius/auxiliary"
stdout: none
--- stderr -------------------------------
error: lifetime may not live long enough
  --> /home/arthur/Git/rust/src/test/ui/closures/closure-expected-type/expect-region-supply-region-2.rs:14:30
   |
LL | fn expect_bound_supply_named<'x>() {
   |                              -- lifetime `'x` defined here
...
LL |     closure_expecting_bound(|x: &'x u32| {
   |                              ^  - let's call the lifetime of this reference `'1`
   |                              |
   |                              requires that `'1` must outlive `'x`

error[E0521]: borrowed data escapes outside of closure
  --> /home/arthur/Git/rust/src/test/ui/closures/closure-expected-type/expect-region-supply-region-2.rs:20:9
   |
LL |     let mut f: Option<&u32> = None;
   |         ----- `f` declared here, outside of the closure body
...
LL |     closure_expecting_bound(|x: &'x u32| {
   |                              - `x` is a reference that is only valid in the closure body
...
LL |         f = Some(x);
   |         ^^^^^^^^^^^ `x` escapes the closure body here

error: lifetime may not live long enough
  --> /home/arthur/Git/rust/src/test/ui/closures/closure-expected-type/expect-region-supply-region-2.rs:14:30
   |
LL | fn expect_bound_supply_named<'x>() {
   |                              -- lifetime `'x` defined here
...
LL |     closure_expecting_bound(|x: &'x u32| {
   |                              ^ requires that `'x` must outlive `'static`

error: aborting due to 3 previous errors

For more information about this error, try `rustc --explain E0521`.
------------------------------------------


---- [ui (polonius)] ui/crate-loading/crateresolve2.rs stdout ----
diff of stderr:

5	   | ^^^^^^^^^^^^^^^^^^^^^^^^^^^
6	   |
7	   = note: candidates:
-	           crate `crateresolve2`: $TEST_BUILD_DIR/crate-loading/crateresolve2/auxiliary/libcrateresolve2-1.rmeta
-	           crate `crateresolve2`: $TEST_BUILD_DIR/crate-loading/crateresolve2/auxiliary/libcrateresolve2-2.rmeta
-	           crate `crateresolve2`: $TEST_BUILD_DIR/crate-loading/crateresolve2/auxiliary/libcrateresolve2-3.rmeta
+	           crate `crateresolve2`: $TEST_BUILD_DIR/crate-loading/crateresolve2.polonius/auxiliary/libcrateresolve2-1.rmeta
+	           crate `crateresolve2`: $TEST_BUILD_DIR/crate-loading/crateresolve2.polonius/auxiliary/libcrateresolve2-2.rmeta
+	           crate `crateresolve2`: $TEST_BUILD_DIR/crate-loading/crateresolve2.polonius/auxiliary/libcrateresolve2-3.rmeta
11	
12	error: aborting due to previous error
13	


The actual stderr differed from the expected stderr.
Actual stderr saved to /home/arthur/Git/rust/build/x86_64-unknown-linux-gnu/test/ui/crate-loading/crateresolve2.polonius/crateresolve2.polonius.stderr
To update references, rerun the tests and pass the `--bless` flag
To only update this specific test, also pass `--test-args crate-loading/crateresolve2.rs`

error: 1 errors occurred comparing output.
status: exit status: 1
command: "/home/arthur/Git/rust/build/x86_64-unknown-linux-gnu/stage1/bin/rustc" "/home/arthur/Git/rust/src/test/ui/crate-loading/crateresolve2.rs" "-Zthreads=1" "--target=x86_64-unknown-linux-gnu" "--error-format" "json" "--json" "future-incompat" "-Ccodegen-units=1" "-Zui-testing" "-Zdeduplicate-diagnostics=no" "--emit" "metadata" "-C" "prefer-dynamic" "--out-dir" "/home/arthur/Git/rust/build/x86_64-unknown-linux-gnu/test/ui/crate-loading/crateresolve2.polonius" "-Zpolonius" "-Zborrowck=mir" "-A" "unused" "-Crpath" "-O" "-Cdebuginfo=0" "-Lnative=/home/arthur/Git/rust/build/x86_64-unknown-linux-gnu/native/rust-test-helpers" "-L" "/home/arthur/Git/rust/build/x86_64-unknown-linux-gnu/test/ui/crate-loading/crateresolve2.polonius/auxiliary"
stdout: none
--- stderr -------------------------------
error[E0464]: multiple matching crates for `crateresolve2`
  --> /home/arthur/Git/rust/src/test/ui/crate-loading/crateresolve2.rs:10:1
   |
LL | extern crate crateresolve2;
   | ^^^^^^^^^^^^^^^^^^^^^^^^^^^
   |
   = note: candidates:
           crate `crateresolve2`: /home/arthur/Git/rust/build/x86_64-unknown-linux-gnu/test/ui/crate-loading/crateresolve2.polonius/auxiliary/libcrateresolve2-1.rmeta
           crate `crateresolve2`: /home/arthur/Git/rust/build/x86_64-unknown-linux-gnu/test/ui/crate-loading/crateresolve2.polonius/auxiliary/libcrateresolve2-2.rmeta
           crate `crateresolve2`: /home/arthur/Git/rust/build/x86_64-unknown-linux-gnu/test/ui/crate-loading/crateresolve2.polonius/auxiliary/libcrateresolve2-3.rmeta

error: aborting due to previous error

For more information about this error, try `rustc --explain E0464`.
------------------------------------------


---- [ui (polonius)] ui/crate-loading/crateresolve1.rs stdout ----
diff of stderr:

5	   | ^^^^^^^^^^^^^^^^^^^^^^^^^^^
6	   |
7	   = note: candidates:
-	           crate `crateresolve1`: $TEST_BUILD_DIR/crate-loading/crateresolve1/auxiliary/libcrateresolve1-1.somelib
-	           crate `crateresolve1`: $TEST_BUILD_DIR/crate-loading/crateresolve1/auxiliary/libcrateresolve1-2.somelib
-	           crate `crateresolve1`: $TEST_BUILD_DIR/crate-loading/crateresolve1/auxiliary/libcrateresolve1-3.somelib
+	           crate `crateresolve1`: $TEST_BUILD_DIR/crate-loading/crateresolve1.polonius/auxiliary/libcrateresolve1-1.somelib
+	           crate `crateresolve1`: $TEST_BUILD_DIR/crate-loading/crateresolve1.polonius/auxiliary/libcrateresolve1-2.somelib
+	           crate `crateresolve1`: $TEST_BUILD_DIR/crate-loading/crateresolve1.polonius/auxiliary/libcrateresolve1-3.somelib
11	
12	error: aborting due to previous error
13	


The actual stderr differed from the expected stderr.
Actual stderr saved to /home/arthur/Git/rust/build/x86_64-unknown-linux-gnu/test/ui/crate-loading/crateresolve1.polonius/crateresolve1.polonius.stderr
To update references, rerun the tests and pass the `--bless` flag
To only update this specific test, also pass `--test-args crate-loading/crateresolve1.rs`

error: 1 errors occurred comparing output.
status: exit status: 1
command: "/home/arthur/Git/rust/build/x86_64-unknown-linux-gnu/stage1/bin/rustc" "/home/arthur/Git/rust/src/test/ui/crate-loading/crateresolve1.rs" "-Zthreads=1" "--target=x86_64-unknown-linux-gnu" "--error-format" "json" "--json" "future-incompat" "-Ccodegen-units=1" "-Zui-testing" "-Zdeduplicate-diagnostics=no" "--emit" "metadata" "-C" "prefer-dynamic" "--out-dir" "/home/arthur/Git/rust/build/x86_64-unknown-linux-gnu/test/ui/crate-loading/crateresolve1.polonius" "-Zpolonius" "-Zborrowck=mir" "-A" "unused" "-Crpath" "-O" "-Cdebuginfo=0" "-Lnative=/home/arthur/Git/rust/build/x86_64-unknown-linux-gnu/native/rust-test-helpers" "-L" "/home/arthur/Git/rust/build/x86_64-unknown-linux-gnu/test/ui/crate-loading/crateresolve1.polonius/auxiliary"
stdout: none
--- stderr -------------------------------
error[E0464]: multiple matching crates for `crateresolve1`
  --> /home/arthur/Git/rust/src/test/ui/crate-loading/crateresolve1.rs:11:1
   |
LL | extern crate crateresolve1;
   | ^^^^^^^^^^^^^^^^^^^^^^^^^^^
   |
   = note: candidates:
           crate `crateresolve1`: /home/arthur/Git/rust/build/x86_64-unknown-linux-gnu/test/ui/crate-loading/crateresolve1.polonius/auxiliary/libcrateresolve1-1.so
           crate `crateresolve1`: /home/arthur/Git/rust/build/x86_64-unknown-linux-gnu/test/ui/crate-loading/crateresolve1.polonius/auxiliary/libcrateresolve1-2.so
           crate `crateresolve1`: /home/arthur/Git/rust/build/x86_64-unknown-linux-gnu/test/ui/crate-loading/crateresolve1.polonius/auxiliary/libcrateresolve1-3.so

error: aborting due to previous error

For more information about this error, try `rustc --explain E0464`.
------------------------------------------


---- [ui (polonius)] ui/error-codes/E0464.rs stdout ----
diff of stderr:

5	   | ^^^^^^^^^^^^^^^^^^^^^^^^^^^
6	   |
7	   = note: candidates:
-	           crate `crateresolve1`: $TEST_BUILD_DIR/error-codes/E0464/auxiliary/libcrateresolve1-1.somelib
-	           crate `crateresolve1`: $TEST_BUILD_DIR/error-codes/E0464/auxiliary/libcrateresolve1-2.somelib
-	           crate `crateresolve1`: $TEST_BUILD_DIR/error-codes/E0464/auxiliary/libcrateresolve1-3.somelib
+	           crate `crateresolve1`: $TEST_BUILD_DIR/error-codes/E0464.polonius/auxiliary/libcrateresolve1-1.somelib
+	           crate `crateresolve1`: $TEST_BUILD_DIR/error-codes/E0464.polonius/auxiliary/libcrateresolve1-2.somelib
+	           crate `crateresolve1`: $TEST_BUILD_DIR/error-codes/E0464.polonius/auxiliary/libcrateresolve1-3.somelib
11	
12	error: aborting due to previous error
13	


The actual stderr differed from the expected stderr.
Actual stderr saved to /home/arthur/Git/rust/build/x86_64-unknown-linux-gnu/test/ui/error-codes/E0464.polonius/E0464.polonius.stderr
To update references, rerun the tests and pass the `--bless` flag
To only update this specific test, also pass `--test-args error-codes/E0464.rs`

error: 1 errors occurred comparing output.
status: exit status: 1
command: "/home/arthur/Git/rust/build/x86_64-unknown-linux-gnu/stage1/bin/rustc" "/home/arthur/Git/rust/src/test/ui/error-codes/E0464.rs" "-Zthreads=1" "--target=x86_64-unknown-linux-gnu" "--error-format" "json" "--json" "future-incompat" "-Ccodegen-units=1" "-Zui-testing" "-Zdeduplicate-diagnostics=no" "--emit" "metadata" "-C" "prefer-dynamic" "--out-dir" "/home/arthur/Git/rust/build/x86_64-unknown-linux-gnu/test/ui/error-codes/E0464.polonius" "-Zpolonius" "-Zborrowck=mir" "-A" "unused" "-Crpath" "-O" "-Cdebuginfo=0" "-Lnative=/home/arthur/Git/rust/build/x86_64-unknown-linux-gnu/native/rust-test-helpers" "-L" "/home/arthur/Git/rust/build/x86_64-unknown-linux-gnu/test/ui/error-codes/E0464.polonius/auxiliary"
stdout: none
--- stderr -------------------------------
error[E0464]: multiple matching crates for `crateresolve1`
  --> /home/arthur/Git/rust/src/test/ui/error-codes/E0464.rs:11:1
   |
LL | extern crate crateresolve1;
   | ^^^^^^^^^^^^^^^^^^^^^^^^^^^
   |
   = note: candidates:
           crate `crateresolve1`: /home/arthur/Git/rust/build/x86_64-unknown-linux-gnu/test/ui/error-codes/E0464.polonius/auxiliary/libcrateresolve1-1.so
           crate `crateresolve1`: /home/arthur/Git/rust/build/x86_64-unknown-linux-gnu/test/ui/error-codes/E0464.polonius/auxiliary/libcrateresolve1-2.so
           crate `crateresolve1`: /home/arthur/Git/rust/build/x86_64-unknown-linux-gnu/test/ui/error-codes/E0464.polonius/auxiliary/libcrateresolve1-3.so

error: aborting due to previous error

For more information about this error, try `rustc --explain E0464`.
------------------------------------------


---- [ui (polonius)] ui/generic-associated-types/issue-91139.rs#migrate stdout ----

error in revision `migrate`: ui test compiled successfully!
status: exit status: 0
command: "/home/arthur/Git/rust/build/x86_64-unknown-linux-gnu/stage1/bin/rustc" "/home/arthur/Git/rust/src/test/ui/generic-associated-types/issue-91139.rs" "-Zthreads=1" "--target=x86_64-unknown-linux-gnu" "--cfg" "migrate" "--error-format" "json" "--json" "future-incompat" "-Ccodegen-units=1" "-Zui-testing" "-Zdeduplicate-diagnostics=no" "--emit" "metadata" "-C" "prefer-dynamic" "--out-dir" "/home/arthur/Git/rust/build/x86_64-unknown-linux-gnu/test/ui/generic-associated-types/issue-91139.migrate.polonius" "-Zpolonius" "-Zborrowck=mir" "-A" "unused" "-Crpath" "-O" "-Cdebuginfo=0" "-Lnative=/home/arthur/Git/rust/build/x86_64-unknown-linux-gnu/native/rust-test-helpers" "-L" "/home/arthur/Git/rust/build/x86_64-unknown-linux-gnu/test/ui/generic-associated-types/issue-91139.migrate.polonius/auxiliary"
stdout: none
stderr: none


---- [ui (polonius)] ui/generic-associated-types/issue-92096.rs#migrate stdout ----

error in revision `migrate`: ui test compiled successfully!
status: exit status: 0
command: "/home/arthur/Git/rust/build/x86_64-unknown-linux-gnu/stage1/bin/rustc" "/home/arthur/Git/rust/src/test/ui/generic-associated-types/issue-92096.rs" "-Zthreads=1" "--target=x86_64-unknown-linux-gnu" "--cfg" "migrate" "--error-format" "json" "--json" "future-incompat" "-Ccodegen-units=1" "-Zui-testing" "-Zdeduplicate-diagnostics=no" "--emit" "metadata" "-C" "prefer-dynamic" "--out-dir" "/home/arthur/Git/rust/build/x86_64-unknown-linux-gnu/test/ui/generic-associated-types/issue-92096.migrate.polonius" "-Zpolonius" "-Zborrowck=mir" "-A" "unused" "-Crpath" "-O" "-Cdebuginfo=0" "-Lnative=/home/arthur/Git/rust/build/x86_64-unknown-linux-gnu/native/rust-test-helpers" "--edition=2018" "-L" "/home/arthur/Git/rust/build/x86_64-unknown-linux-gnu/test/ui/generic-associated-types/issue-92096.migrate.polonius/auxiliary"
stdout: none
stderr: none


---- [ui (polonius)] ui/higher-rank-trait-bounds/normalize-under-binder/issue-71955.rs#migrate stdout ----
diff of stderr:

-	error: implementation of `Parser` is not general enough
+	error[E0308]: mismatched types
2	  --> $DIR/issue-71955.rs:54:5
3	   |
4	LL |     foo(bar, "string", |s| s.len() == 5);

-	   |     ^^^ implementation of `Parser` is not general enough
+	   |     ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ one type is more general than the other
6	   |
-	   = note: `for<'a> fn(&'a str) -> (&'a str, &'a str) {bar}` must implement `Parser<'0>`, for any lifetime `'0`...
-	   = note: ...but it actually implements `Parser<'1>`, for some specific lifetime `'1`
+	   = note: expected type `for<'r, 's> FnOnce<(&'r &'s str,)>`
+	              found type `for<'r> FnOnce<(&'r &str,)>`
+	note: this closure does not fulfill the lifetime requirements
+	  --> $DIR/issue-71955.rs:54:24
+	   |
+	LL |     foo(bar, "string", |s| s.len() == 5);
+	   |                        ^^^^^^^^^^^^^^^^
+	note: the lifetime requirement is introduced here
+	  --> $DIR/issue-71955.rs:34:9
+	   |
+	LL |     F2: FnOnce(&<F1 as Parser>::Output) -> bool
+	   |         ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
9	
-	error: implementation of `Parser` is not general enough
+	error[E0308]: mismatched types
+	  --> $DIR/issue-71955.rs:54:5
+	   |
+	LL |     foo(bar, "string", |s| s.len() == 5);
+	   |     ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ one type is more general than the other
+	   |
+	   = note: expected type `FnOnce<(&&str,)>`
+	              found type `for<'r> FnOnce<(&'r &str,)>`
+	note: this closure does not fulfill the lifetime requirements
+	  --> $DIR/issue-71955.rs:54:24
+	   |
+	LL |     foo(bar, "string", |s| s.len() == 5);
+	   |                        ^^^^^^^^^^^^^^^^
+	note: the lifetime requirement is introduced here
+	  --> $DIR/issue-71955.rs:34:44
+	   |
+	LL |     F2: FnOnce(&<F1 as Parser>::Output) -> bool
+	   |                                            ^^^^
+	
+	error[E0308]: mismatched types
11	  --> $DIR/issue-71955.rs:58:5
12	   |
13	LL |     foo(baz, "string", |s| s.0.len() == 5);

-	   |     ^^^ implementation of `Parser` is not general enough
+	   |     ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ one type is more general than the other
15	   |
-	   = note: `for<'a> fn(&'a str) -> (&'a str, Wrapper<'a>) {baz}` must implement `Parser<'0>`, for any lifetime `'0`...
-	   = note: ...but it actually implements `Parser<'1>`, for some specific lifetime `'1`
+	   = note: expected type `for<'r, 's> FnOnce<(&'r Wrapper<'s>,)>`
+	              found type `for<'r> FnOnce<(&'r Wrapper<'_>,)>`
+	note: this closure does not fulfill the lifetime requirements
+	  --> $DIR/issue-71955.rs:58:24
+	   |
+	LL |     foo(baz, "string", |s| s.0.len() == 5);
+	   |                        ^^^^^^^^^^^^^^^^^^
+	note: the lifetime requirement is introduced here
+	  --> $DIR/issue-71955.rs:34:9
+	   |
+	LL |     F2: FnOnce(&<F1 as Parser>::Output) -> bool
+	   |         ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
18	
-	error: aborting due to 2 previous errors
+	error[E0308]: mismatched types
+	  --> $DIR/issue-71955.rs:58:5
+	   |
+	LL |     foo(baz, "string", |s| s.0.len() == 5);
+	   |     ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ one type is more general than the other
+	   |
+	   = note: expected type `FnOnce<(&Wrapper<'_>,)>`
+	              found type `for<'r> FnOnce<(&'r Wrapper<'_>,)>`
+	note: this closure does not fulfill the lifetime requirements
+	  --> $DIR/issue-71955.rs:58:24
+	   |
+	LL |     foo(baz, "string", |s| s.0.len() == 5);
+	   |                        ^^^^^^^^^^^^^^^^^^
+	note: the lifetime requirement is introduced here
+	  --> $DIR/issue-71955.rs:34:44
+	   |
+	LL |     F2: FnOnce(&<F1 as Parser>::Output) -> bool
+	   |                                            ^^^^
20	
+	error: aborting due to 4 previous errors
+	
+	For more information about this error, try `rustc --explain E0308`.
21	


The actual stderr differed from the expected stderr.
Actual stderr saved to /home/arthur/Git/rust/build/x86_64-unknown-linux-gnu/test/ui/higher-rank-trait-bounds/normalize-under-binder/issue-71955.migrate.polonius/issue-71955.migrate.polonius.stderr
To update references, rerun the tests and pass the `--bless` flag
To only update this specific test, also pass `--test-args higher-rank-trait-bounds/normalize-under-binder/issue-71955.rs`

error in revision `migrate`: 1 errors occurred comparing output.
status: exit status: 1
command: "/home/arthur/Git/rust/build/x86_64-unknown-linux-gnu/stage1/bin/rustc" "/home/arthur/Git/rust/src/test/ui/higher-rank-trait-bounds/normalize-under-binder/issue-71955.rs" "-Zthreads=1" "--target=x86_64-unknown-linux-gnu" "--cfg" "migrate" "--error-format" "json" "--json" "future-incompat" "-Ccodegen-units=1" "-Zui-testing" "-Zdeduplicate-diagnostics=no" "--emit" "metadata" "-C" "prefer-dynamic" "--out-dir" "/home/arthur/Git/rust/build/x86_64-unknown-linux-gnu/test/ui/higher-rank-trait-bounds/normalize-under-binder/issue-71955.migrate.polonius" "-Zpolonius" "-Zborrowck=mir" "-A" "unused" "-Crpath" "-O" "-Cdebuginfo=0" "-Lnative=/home/arthur/Git/rust/build/x86_64-unknown-linux-gnu/native/rust-test-helpers" "-L" "/home/arthur/Git/rust/build/x86_64-unknown-linux-gnu/test/ui/higher-rank-trait-bounds/normalize-under-binder/issue-71955.migrate.polonius/auxiliary"
stdout: none
--- stderr -------------------------------
error[E0308]: mismatched types
  --> /home/arthur/Git/rust/src/test/ui/higher-rank-trait-bounds/normalize-under-binder/issue-71955.rs:54:5
   |
LL |     foo(bar, "string", |s| s.len() == 5);
   |     ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ one type is more general than the other
   |
   = note: expected type `for<'r, 's> FnOnce<(&'r &'s str,)>`
              found type `for<'r> FnOnce<(&'r &str,)>`
note: this closure does not fulfill the lifetime requirements
  --> /home/arthur/Git/rust/src/test/ui/higher-rank-trait-bounds/normalize-under-binder/issue-71955.rs:54:24
   |
LL |     foo(bar, "string", |s| s.len() == 5);
   |                        ^^^^^^^^^^^^^^^^
note: the lifetime requirement is introduced here
  --> /home/arthur/Git/rust/src/test/ui/higher-rank-trait-bounds/normalize-under-binder/issue-71955.rs:34:9
   |
LL |     F2: FnOnce(&<F1 as Parser>::Output) -> bool
   |         ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

error[E0308]: mismatched types
  --> /home/arthur/Git/rust/src/test/ui/higher-rank-trait-bounds/normalize-under-binder/issue-71955.rs:54:5
   |
LL |     foo(bar, "string", |s| s.len() == 5);
   |     ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ one type is more general than the other
   |
   = note: expected type `FnOnce<(&&str,)>`
              found type `for<'r> FnOnce<(&'r &str,)>`
note: this closure does not fulfill the lifetime requirements
  --> /home/arthur/Git/rust/src/test/ui/higher-rank-trait-bounds/normalize-under-binder/issue-71955.rs:54:24
   |
LL |     foo(bar, "string", |s| s.len() == 5);
   |                        ^^^^^^^^^^^^^^^^
note: the lifetime requirement is introduced here
  --> /home/arthur/Git/rust/src/test/ui/higher-rank-trait-bounds/normalize-under-binder/issue-71955.rs:34:44
   |
LL |     F2: FnOnce(&<F1 as Parser>::Output) -> bool
   |                                            ^^^^

error[E0308]: mismatched types
  --> /home/arthur/Git/rust/src/test/ui/higher-rank-trait-bounds/normalize-under-binder/issue-71955.rs:58:5
   |
LL |     foo(baz, "string", |s| s.0.len() == 5);
   |     ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ one type is more general than the other
   |
   = note: expected type `for<'r, 's> FnOnce<(&'r Wrapper<'s>,)>`
              found type `for<'r> FnOnce<(&'r Wrapper<'_>,)>`
note: this closure does not fulfill the lifetime requirements
  --> /home/arthur/Git/rust/src/test/ui/higher-rank-trait-bounds/normalize-under-binder/issue-71955.rs:58:24
   |
LL |     foo(baz, "string", |s| s.0.len() == 5);
   |                        ^^^^^^^^^^^^^^^^^^
note: the lifetime requirement is introduced here
  --> /home/arthur/Git/rust/src/test/ui/higher-rank-trait-bounds/normalize-under-binder/issue-71955.rs:34:9
   |
LL |     F2: FnOnce(&<F1 as Parser>::Output) -> bool
   |         ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

error[E0308]: mismatched types
  --> /home/arthur/Git/rust/src/test/ui/higher-rank-trait-bounds/normalize-under-binder/issue-71955.rs:58:5
   |
LL |     foo(baz, "string", |s| s.0.len() == 5);
   |     ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ one type is more general than the other
   |
   = note: expected type `FnOnce<(&Wrapper<'_>,)>`
              found type `for<'r> FnOnce<(&'r Wrapper<'_>,)>`
note: this closure does not fulfill the lifetime requirements
  --> /home/arthur/Git/rust/src/test/ui/higher-rank-trait-bounds/normalize-under-binder/issue-71955.rs:58:24
   |
LL |     foo(baz, "string", |s| s.0.len() == 5);
   |                        ^^^^^^^^^^^^^^^^^^
note: the lifetime requirement is introduced here
  --> /home/arthur/Git/rust/src/test/ui/higher-rank-trait-bounds/normalize-under-binder/issue-71955.rs:34:44
   |
LL |     F2: FnOnce(&<F1 as Parser>::Output) -> bool
   |                                            ^^^^

error: aborting due to 4 previous errors

For more information about this error, try `rustc --explain E0308`.
------------------------------------------


---- [ui (polonius)] ui/hrtb/hrtb-just-for-static.rs stdout ----
diff of stderr:

7	   = note: `StaticInt` must implement `Foo<&'0 isize>`, for any lifetime `'0`...
8	   = note: ...but it actually implements `Foo<&'static isize>`
9	
-	error: lifetime may not live long enough
-	  --> $DIR/hrtb-just-for-static.rs:30:5
-	   |
-	LL | fn give_some<'a>() {
-	   |              -- lifetime `'a` defined here
-	LL |     want_hrtb::<&'a u32>()
-	   |     ^^^^^^^^^^^^^^^^^^^^ requires that `'a` must outlive `'static`
-	
18	error: implementation of `Foo` is not general enough
19	  --> $DIR/hrtb-just-for-static.rs:30:5
20	   |

24	   = note: `Foo<&'0 isize>` would have to be implemented for the type `&u32`, for any lifetime `'0`...
25	   = note: ...but `Foo<&'1 isize>` is actually implemented for the type `&'1 u32`, for some specific lifetime `'1`
26	
-	error: aborting due to 3 previous errors
+	error: aborting due to 2 previous errors
28	
29	


The actual stderr differed from the expected stderr.
Actual stderr saved to /home/arthur/Git/rust/build/x86_64-unknown-linux-gnu/test/ui/hrtb/hrtb-just-for-static.polonius/hrtb-just-for-static.polonius.stderr
To update references, rerun the tests and pass the `--bless` flag
To only update this specific test, also pass `--test-args hrtb/hrtb-just-for-static.rs`

error: 1 errors occurred comparing output.
status: exit status: 1
command: "/home/arthur/Git/rust/build/x86_64-unknown-linux-gnu/stage1/bin/rustc" "/home/arthur/Git/rust/src/test/ui/hrtb/hrtb-just-for-static.rs" "-Zthreads=1" "--target=x86_64-unknown-linux-gnu" "--error-format" "json" "--json" "future-incompat" "-Ccodegen-units=1" "-Zui-testing" "-Zdeduplicate-diagnostics=no" "--emit" "metadata" "-C" "prefer-dynamic" "--out-dir" "/home/arthur/Git/rust/build/x86_64-unknown-linux-gnu/test/ui/hrtb/hrtb-just-for-static.polonius" "-Zpolonius" "-Zborrowck=mir" "-A" "unused" "-Crpath" "-O" "-Cdebuginfo=0" "-Lnative=/home/arthur/Git/rust/build/x86_64-unknown-linux-gnu/native/rust-test-helpers" "-L" "/home/arthur/Git/rust/build/x86_64-unknown-linux-gnu/test/ui/hrtb/hrtb-just-for-static.polonius/auxiliary"
stdout: none
--- stderr -------------------------------
error: implementation of `Foo` is not general enough
  --> /home/arthur/Git/rust/src/test/ui/hrtb/hrtb-just-for-static.rs:24:5
   |
LL |     want_hrtb::<StaticInt>() //~ ERROR
   |     ^^^^^^^^^^^^^^^^^^^^^^^^ implementation of `Foo` is not general enough
   |
   = note: `StaticInt` must implement `Foo<&'0 isize>`, for any lifetime `'0`...
   = note: ...but it actually implements `Foo<&'static isize>`

error: implementation of `Foo` is not general enough
  --> /home/arthur/Git/rust/src/test/ui/hrtb/hrtb-just-for-static.rs:30:5
   |
LL |     want_hrtb::<&'a u32>() //~ ERROR
   |     ^^^^^^^^^^^^^^^^^^^^ implementation of `Foo` is not general enough
   |
   = note: `Foo<&'0 isize>` would have to be implemented for the type `&u32`, for any lifetime `'0`...
   = note: ...but `Foo<&'1 isize>` is actually implemented for the type `&'1 u32`, for some specific lifetime `'1`

error: aborting due to 2 previous errors
------------------------------------------


---- [ui (polonius)] ui/hrtb/hrtb-perfect-forwarding.rs stdout ----
diff of stderr:

46	   |
47	   = help: a `loop` may express intention better if this is on purpose
48	
-	error: higher-ranked subtype error
+	error: implementation of `Bar` is not general enough
50	  --> $DIR/hrtb-perfect-forwarding.rs:43:5
51	   |
52	LL |     foo_hrtb_bar_not(&mut t);

-	   |     ^^^^^^^^^^^^^^^^^^^^^^^^
+	   |     ^^^^^^^^^^^^^^^^^^^^^^^^ implementation of `Bar` is not general enough
+	   |
+	   = note: `T` must implement `Bar<&'0 isize>`, for any lifetime `'0`...
+	   = note: ...but it actually implements `Bar<&'1 isize>`, for some specific lifetime `'1`
54	
55	warning: function cannot return without recursing
56	  --> $DIR/hrtb-perfect-forwarding.rs:48:1


The actual stderr differed from the expected stderr.
Actual stderr saved to /home/arthur/Git/rust/build/x86_64-unknown-linux-gnu/test/ui/hrtb/hrtb-perfect-forwarding.polonius/hrtb-perfect-forwarding.polonius.stderr
To update references, rerun the tests and pass the `--bless` flag
To only update this specific test, also pass `--test-args hrtb/hrtb-perfect-forwarding.rs`

error: 1 errors occurred comparing output.
status: exit status: 1
command: "/home/arthur/Git/rust/build/x86_64-unknown-linux-gnu/stage1/bin/rustc" "/home/arthur/Git/rust/src/test/ui/hrtb/hrtb-perfect-forwarding.rs" "-Zthreads=1" "--target=x86_64-unknown-linux-gnu" "--error-format" "json" "--json" "future-incompat" "-Ccodegen-units=1" "-Zui-testing" "-Zdeduplicate-diagnostics=no" "--emit" "metadata" "-C" "prefer-dynamic" "--out-dir" "/home/arthur/Git/rust/build/x86_64-unknown-linux-gnu/test/ui/hrtb/hrtb-perfect-forwarding.polonius" "-Zpolonius" "-Zborrowck=mir" "-A" "unused" "-Crpath" "-O" "-Cdebuginfo=0" "-Lnative=/home/arthur/Git/rust/build/x86_64-unknown-linux-gnu/native/rust-test-helpers" "-L" "/home/arthur/Git/rust/build/x86_64-unknown-linux-gnu/test/ui/hrtb/hrtb-perfect-forwarding.polonius/auxiliary"
stdout: none
--- stderr -------------------------------
warning: function cannot return without recursing
  --> /home/arthur/Git/rust/src/test/ui/hrtb/hrtb-perfect-forwarding.rs:16:1
   |
LL | / fn no_hrtb<'b, T>(mut t: T)
LL | | where
LL | |     T: Bar<&'b isize>,
LL | | {
...  |
LL | |     no_hrtb(&mut t);
   | |     --------------- recursive call site
LL | | }
   | |_^ cannot return without recursing
   |
   = note: `#[warn(unconditional_recursion)]` on by default
   = help: a `loop` may express intention better if this is on purpose

warning: function cannot return without recursing
  --> /home/arthur/Git/rust/src/test/ui/hrtb/hrtb-perfect-forwarding.rs:25:1
   |
LL | / fn bar_hrtb<T>(mut t: T)
LL | | where
LL | |     T: for<'b> Bar<&'b isize>,
LL | | {
...  |
LL | |     bar_hrtb(&mut t);
   | |     ---------------- recursive call site
LL | | }
   | |_^ cannot return without recursing
   |
   = help: a `loop` may express intention better if this is on purpose

warning: function cannot return without recursing
  --> /home/arthur/Git/rust/src/test/ui/hrtb/hrtb-perfect-forwarding.rs:35:1
   |
LL | / fn foo_hrtb_bar_not<'b, T>(mut t: T)
LL | | where
LL | |     T: for<'a> Foo<&'a isize> + Bar<&'b isize>,
LL | | {
...  |
LL | |     foo_hrtb_bar_not(&mut t);
   | |     ------------------------ recursive call site
LL | |     //~^ ERROR implementation of `Bar` is not general enough
LL | |     //~| ERROR implementation of `Bar` is not general enough
LL | | }
   | |_^ cannot return without recursing
   |
   = help: a `loop` may express intention better if this is on purpose

error: implementation of `Bar` is not general enough
  --> /home/arthur/Git/rust/src/test/ui/hrtb/hrtb-perfect-forwarding.rs:43:5
   |
LL |     foo_hrtb_bar_not(&mut t);
   |     ^^^^^^^^^^^^^^^^^^^^^^^^ implementation of `Bar` is not general enough
   |
   = note: `T` must implement `Bar<&'0 isize>`, for any lifetime `'0`...
   = note: ...but it actually implements `Bar<&'1 isize>`, for some specific lifetime `'1`

warning: function cannot return without recursing
  --> /home/arthur/Git/rust/src/test/ui/hrtb/hrtb-perfect-forwarding.rs:48:1
   |
LL | / fn foo_hrtb_bar_hrtb<T>(mut t: T)
LL | | where
LL | |     T: for<'a> Foo<&'a isize> + for<'b> Bar<&'b isize>,
LL | | {
LL | |     // OK -- now we have `T : for<'b> Bar<&'b isize>`.
LL | |     foo_hrtb_bar_hrtb(&mut t);
   | |     ------------------------- recursive call site
LL | | }
   | |_^ cannot return without recursing
   |
   = help: a `loop` may express intention better if this is on purpose

error: aborting due to previous error; 4 warnings emitted
------------------------------------------


---- [ui (polonius)] ui/impl-trait/multiple-lifetimes/error-handling.rs stdout ----
diff of stderr:

1	error: lifetime may not live long enough
-	  --> $DIR/error-handling.rs:22:16
+	  --> $DIR/error-handling.rs:20:16
3	   |
4	LL | fn foo<'a, 'b, 'c>(x: &'static i32, mut y: &'a i32) -> E<'b, 'c> {
5	   |        --  -- lifetime `'b` defined here


The actual stderr differed from the expected stderr.
Actual stderr saved to /home/arthur/Git/rust/build/x86_64-unknown-linux-gnu/test/ui/impl-trait/multiple-lifetimes/error-handling.polonius/error-handling.polonius.stderr
To update references, rerun the tests and pass the `--bless` flag
To only update this specific test, also pass `--test-args impl-trait/multiple-lifetimes/error-handling.rs`

error: 1 errors occurred comparing output.
status: exit status: 1
command: "/home/arthur/Git/rust/build/x86_64-unknown-linux-gnu/stage1/bin/rustc" "/home/arthur/Git/rust/src/test/ui/impl-trait/multiple-lifetimes/error-handling.rs" "-Zthreads=1" "--target=x86_64-unknown-linux-gnu" "--error-format" "json" "--json" "future-incompat" "-Ccodegen-units=1" "-Zui-testing" "-Zdeduplicate-diagnostics=no" "--emit" "metadata" "-C" "prefer-dynamic" "--out-dir" "/home/arthur/Git/rust/build/x86_64-unknown-linux-gnu/test/ui/impl-trait/multiple-lifetimes/error-handling.polonius" "-Zpolonius" "-Zborrowck=mir" "-A" "unused" "-Crpath" "-O" "-Cdebuginfo=0" "-Lnative=/home/arthur/Git/rust/build/x86_64-unknown-linux-gnu/native/rust-test-helpers" "-L" "/home/arthur/Git/rust/build/x86_64-unknown-linux-gnu/test/ui/impl-trait/multiple-lifetimes/error-handling.polonius/auxiliary"
stdout: none
--- stderr -------------------------------
error: lifetime may not live long enough
  --> /home/arthur/Git/rust/src/test/ui/impl-trait/multiple-lifetimes/error-handling.rs:20:16
   |
LL | fn foo<'a, 'b, 'c>(x: &'static i32, mut y: &'a i32) -> E<'b, 'c> {
   |        --  -- lifetime `'b` defined here
   |        |
   |        lifetime `'a` defined here
...
LL |         let _: &'b i32 = *u.0;
   |                ^^^^^^^ type annotation requires that `'a` must outlive `'b`
   |
   = help: consider adding the following bound: `'a: 'b`

error: aborting due to previous error
------------------------------------------


---- [ui (polonius)] ui/issues/issue-26217.rs stdout ----

error: ui test compiled successfully!
status: exit status: 0
command: "/home/arthur/Git/rust/build/x86_64-unknown-linux-gnu/stage1/bin/rustc" "/home/arthur/Git/rust/src/test/ui/issues/issue-26217.rs" "-Zthreads=1" "--target=x86_64-unknown-linux-gnu" "--error-format" "json" "--json" "future-incompat" "-Ccodegen-units=1" "-Zui-testing" "-Zdeduplicate-diagnostics=no" "--emit" "metadata" "-C" "prefer-dynamic" "--out-dir" "/home/arthur/Git/rust/build/x86_64-unknown-linux-gnu/test/ui/issues/issue-26217.polonius" "-Zpolonius" "-Zborrowck=mir" "-A" "unused" "-Crpath" "-O" "-Cdebuginfo=0" "-Lnative=/home/arthur/Git/rust/build/x86_64-unknown-linux-gnu/native/rust-test-helpers" "-L" "/home/arthur/Git/rust/build/x86_64-unknown-linux-gnu/test/ui/issues/issue-26217.polonius/auxiliary"
stdout: none
stderr: none


---- [ui (polonius)] ui/nll/get_default.rs stdout ----
diff of stderr:

5	   |             - let's call the lifetime of this reference `'1`
6	LL |     loop {
7	LL |         match map.get() {
-	   |               --- immutable borrow occurs here
+	   |               --------- immutable borrow occurs here
9	LL |             Some(v) => {
10	LL |                 map.set(String::new()); // Both AST and MIR error here
-	   |                 ^^^ mutable borrow occurs here
+	   |                 ^^^^^^^^^^^^^^^^^^^^^^ mutable borrow occurs here
12	LL |
13	LL |                 return v;
14	   |                        - returning this value requires that `*map` is borrowed for `'1`


The actual stderr differed from the expected stderr.
Actual stderr saved to /home/arthur/Git/rust/build/x86_64-unknown-linux-gnu/test/ui/nll/get_default.polonius/get_default.polonius.stderr
To update references, rerun the tests and pass the `--bless` flag
To only update this specific test, also pass `--test-args nll/get_default.rs`

error: 1 errors occurred comparing output.
status: exit status: 1
command: "/home/arthur/Git/rust/build/x86_64-unknown-linux-gnu/stage1/bin/rustc" "/home/arthur/Git/rust/src/test/ui/nll/get_default.rs" "-Zthreads=1" "--target=x86_64-unknown-linux-gnu" "--error-format" "json" "--json" "future-incompat" "-Ccodegen-units=1" "-Zui-testing" "-Zdeduplicate-diagnostics=no" "--emit" "metadata" "-C" "prefer-dynamic" "--out-dir" "/home/arthur/Git/rust/build/x86_64-unknown-linux-gnu/test/ui/nll/get_default.polonius" "-Zpolonius" "-Zborrowck=mir" "-A" "unused" "-Crpath" "-O" "-Cdebuginfo=0" "-Lnative=/home/arthur/Git/rust/build/x86_64-unknown-linux-gnu/native/rust-test-helpers" "-L" "/home/arthur/Git/rust/build/x86_64-unknown-linux-gnu/test/ui/nll/get_default.polonius/auxiliary"
stdout: none
--- stderr -------------------------------
error[E0502]: cannot borrow `*map` as mutable because it is also borrowed as immutable
  --> /home/arthur/Git/rust/src/test/ui/nll/get_default.rs:32:17
   |
LL | fn err(map: &mut Map) -> &String {
   |             - let's call the lifetime of this reference `'1`
LL |     loop {
LL |         match map.get() {
   |               --------- immutable borrow occurs here
LL |             Some(v) => {
LL |                 map.set(String::new()); // Both AST and MIR error here
   |                 ^^^^^^^^^^^^^^^^^^^^^^ mutable borrow occurs here
LL |                 //~^ ERROR borrowed as immutable
LL |                 return v;
   |                        - returning this value requires that `*map` is borrowed for `'1`

error: aborting due to previous error

For more information about this error, try `rustc --explain E0502`.
------------------------------------------


---- [ui (polonius)] ui/nll/lint-no-err.rs stdout ----

error: test compilation failed although it shouldn't!
status: exit status: 1
command: "/home/arthur/Git/rust/build/x86_64-unknown-linux-gnu/stage1/bin/rustc" "/home/arthur/Git/rust/src/test/ui/nll/lint-no-err.rs" "-Zthreads=1" "--target=x86_64-unknown-linux-gnu" "--error-format" "json" "--json" "future-incompat" "-Ccodegen-units=1" "-Zui-testing" "-Zdeduplicate-diagnostics=no" "--emit" "metadata" "-C" "prefer-dynamic" "--out-dir" "/home/arthur/Git/rust/build/x86_64-unknown-linux-gnu/test/ui/nll/lint-no-err.polonius" "-Zpolonius" "-Zborrowck=mir" "-A" "unused" "-Crpath" "-O" "-Cdebuginfo=0" "-Lnative=/home/arthur/Git/rust/build/x86_64-unknown-linux-gnu/native/rust-test-helpers" "-L" "/home/arthur/Git/rust/build/x86_64-unknown-linux-gnu/test/ui/nll/lint-no-err.polonius/auxiliary"
stdout: none
--- stderr -------------------------------
error[E0502]: cannot borrow `conflict` as mutable because it is also borrowed as immutable
  --> /home/arthur/Git/rust/src/test/ui/nll/lint-no-err.rs:25:5
   |
LL |     let prev = conflict.get();
   |                -------------- immutable borrow occurs here
LL |     conflict.insert(*prev + *x);
   |     ^^^^^^^^^^^^^^^^-----^^^^^^
   |     |               |
   |     |               immutable borrow later used here
   |     mutable borrow occurs here

error: aborting due to previous error

For more information about this error, try `rustc --explain E0502`.
------------------------------------------


---- [ui (polonius)] ui/nll/outlives-suggestion-simple.rs stdout ----
diff of stderr:

6	   |         |
7	   |         lifetime `'a` defined here
8	LL |     x
-	   |     ^ returning this value requires that `'a` must outlive `'b`
+	   |     ^ function was supposed to return data with lifetime `'b` but it is returning data with lifetime `'a`
10	   |
11	   = help: consider adding the following bound: `'a: 'b`
12	

17	   |         -- lifetime `'a` defined here
18	LL |     x
19	   |     ^ returning this value requires that `'a` must outlive `'static`
-	   |
-	   = help: consider replacing `'a` with `'static`
22	
23	error: lifetime may not live long enough
24	  --> $DIR/outlives-suggestion-simple.rs:14:5

55	   |         lifetime `'a` defined here
56	...
57	LL |     (x, x)
-	   |     ^^^^^^ returning this value requires that `'a` must outlive `'b`
+	   |     ^^^^^^ function was supposed to return data with lifetime `'b` but it is returning data with lifetime `'a`
59	   |
60	   = help: consider adding the following bound: `'a: 'b`
61	

68	   |         lifetime `'a` defined here
69	...
70	LL |     (x, x)
-	   |     ^^^^^^ returning this value requires that `'a` must outlive `'c`
+	   |     ^^^^^^ function was supposed to return data with lifetime `'c` but it is returning data with lifetime `'a`
72	   |
73	   = help: consider adding the following bound: `'a: 'c`
74	

81	   |                -- lifetime `'a` defined here
82	LL |         Foo { x }
83	   |         ^^^^^^^^^ returning this value requires that `'a` must outlive `'static`
-	   |
-	   = help: consider replacing `'a` with `'static`
86	
87	error: lifetime may not live long enough
88	  --> $DIR/outlives-suggestion-simple.rs:41:9

92	LL |     pub fn get<'b>(&self) -> &'b usize {
93	   |                -- lifetime `'b` defined here
94	LL |         self.x
-	   |         ^^^^^^ returning this value requires that `'a` must outlive `'b`
+	   |         ^^^^^^ associated function was supposed to return data with lifetime `'b` but it is returning data with lifetime `'a`
96	   |
97	   = help: consider adding the following bound: `'a: 'b`
98	

104	LL |     fn get<'b>(&'b self) -> &'a i32 {
105	   |            -- lifetime `'b` defined here
106	LL |         self.x
-	   |         ^^^^^^ returning this value requires that `'b` must outlive `'a`
+	   |         ^^^^^^ associated function was supposed to return data with lifetime `'a` but it is returning data with lifetime `'b`
108	   |
109	   = help: consider adding the following bound: `'b: 'a`
110	

-	error[E0521]: borrowed data escapes outside of associated function
+	error: lifetime may not live long enough
112	  --> $DIR/outlives-suggestion-simple.rs:73:9
113	   |
+	LL | impl<'a> Foo2<'a> {
+	   |      -- lifetime `'a` defined here
+	LL |     // should not produce outlives suggestions to name 'self
114	LL |     fn get_bar(&self) -> Bar2 {
-	   |                -----
-	   |                |
-	   |                `self` declared here, outside of the associated function body
-	   |                `self` is a reference that is only valid in the associated function body
+	   |                - let's call the lifetime of this reference `'1`
119	LL |         Bar2::new(&self)
-	   |         ^^^^^^^^^^^^^^^^ `self` escapes the associated function body here
+	   |         ^^^^^^^^^^^^^^^^ argument requires that `'1` must outlive `'a`
121	
122	error: aborting due to 10 previous errors
123	

-	For more information about this error, try `rustc --explain E0521`.
125	


The actual stderr differed from the expected stderr.
Actual stderr saved to /home/arthur/Git/rust/build/x86_64-unknown-linux-gnu/test/ui/nll/outlives-suggestion-simple.polonius/outlives-suggestion-simple.polonius.stderr
To update references, rerun the tests and pass the `--bless` flag
To only update this specific test, also pass `--test-args nll/outlives-suggestion-simple.rs`

error: 1 errors occurred comparing output.
status: exit status: 1
command: "/home/arthur/Git/rust/build/x86_64-unknown-linux-gnu/stage1/bin/rustc" "/home/arthur/Git/rust/src/test/ui/nll/outlives-suggestion-simple.rs" "-Zthreads=1" "--target=x86_64-unknown-linux-gnu" "--error-format" "json" "--json" "future-incompat" "-Ccodegen-units=1" "-Zui-testing" "-Zdeduplicate-diagnostics=no" "--emit" "metadata" "-C" "prefer-dynamic" "--out-dir" "/home/arthur/Git/rust/build/x86_64-unknown-linux-gnu/test/ui/nll/outlives-suggestion-simple.polonius" "-Zpolonius" "-Zborrowck=mir" "-A" "unused" "-Crpath" "-O" "-Cdebuginfo=0" "-Lnative=/home/arthur/Git/rust/build/x86_64-unknown-linux-gnu/native/rust-test-helpers" "-L" "/home/arthur/Git/rust/build/x86_64-unknown-linux-gnu/test/ui/nll/outlives-suggestion-simple.polonius/auxiliary"
stdout: none
--- stderr -------------------------------
error: lifetime may not live long enough
  --> /home/arthur/Git/rust/src/test/ui/nll/outlives-suggestion-simple.rs:6:5
   |
LL | fn foo1<'a, 'b>(x: &'a usize) -> &'b usize {
   |         --  -- lifetime `'b` defined here
   |         |
   |         lifetime `'a` defined here
LL |     x //~ERROR lifetime may not live long enough
   |     ^ function was supposed to return data with lifetime `'b` but it is returning data with lifetime `'a`
   |
   = help: consider adding the following bound: `'a: 'b`

error: lifetime may not live long enough
  --> /home/arthur/Git/rust/src/test/ui/nll/outlives-suggestion-simple.rs:10:5
   |
LL | fn foo2<'a>(x: &'a usize) -> &'static usize {
   |         -- lifetime `'a` defined here
LL |     x //~ERROR lifetime may not live long enough
   |     ^ returning this value requires that `'a` must outlive `'static`

error: lifetime may not live long enough
  --> /home/arthur/Git/rust/src/test/ui/nll/outlives-suggestion-simple.rs:14:5
   |
LL | fn foo3<'a, 'b>(x: &'a usize, y: &'b usize) -> (&'b usize, &'a usize) {
   |         --  -- lifetime `'b` defined here
   |         |
   |         lifetime `'a` defined here
LL |     (x, y) //~ERROR lifetime may not live long enough
   |     ^^^^^^ function was supposed to return data with lifetime `'b` but it is returning data with lifetime `'a`
   |
   = help: consider adding the following bound: `'a: 'b`

error: lifetime may not live long enough
  --> /home/arthur/Git/rust/src/test/ui/nll/outlives-suggestion-simple.rs:14:5
   |
LL | fn foo3<'a, 'b>(x: &'a usize, y: &'b usize) -> (&'b usize, &'a usize) {
   |         --  -- lifetime `'b` defined here
   |         |
   |         lifetime `'a` defined here
LL |     (x, y) //~ERROR lifetime may not live long enough
   |     ^^^^^^ function was supposed to return data with lifetime `'a` but it is returning data with lifetime `'b`
   |
   = help: consider adding the following bound: `'b: 'a`

help: `'a` and `'b` must be the same: replace one with the other

error: lifetime may not live long enough
  --> /home/arthur/Git/rust/src/test/ui/nll/outlives-suggestion-simple.rs:22:5
   |
LL | fn foo4<'a, 'b, 'c>(x: &'a usize) -> (&'b usize, &'c usize) {
   |         --  -- lifetime `'b` defined here
   |         |
   |         lifetime `'a` defined here
...
LL |     (x, x) //~ERROR lifetime may not live long enough
   |     ^^^^^^ function was supposed to return data with lifetime `'b` but it is returning data with lifetime `'a`
   |
   = help: consider adding the following bound: `'a: 'b`

error: lifetime may not live long enough
  --> /home/arthur/Git/rust/src/test/ui/nll/outlives-suggestion-simple.rs:22:5
   |
LL | fn foo4<'a, 'b, 'c>(x: &'a usize) -> (&'b usize, &'c usize) {
   |         --      -- lifetime `'c` defined here
   |         |
   |         lifetime `'a` defined here
...
LL |     (x, x) //~ERROR lifetime may not live long enough
   |     ^^^^^^ function was supposed to return data with lifetime `'c` but it is returning data with lifetime `'a`
   |
   = help: consider adding the following bound: `'a: 'c`

help: add bound `'a: 'b + 'c`

error: lifetime may not live long enough
  --> /home/arthur/Git/rust/src/test/ui/nll/outlives-suggestion-simple.rs:31:9
   |
LL |     pub fn foo<'a>(x: &'a usize) -> Self {
   |                -- lifetime `'a` defined here
LL |         Foo { x } //~ERROR lifetime may not live long enough
   |         ^^^^^^^^^ returning this value requires that `'a` must outlive `'static`

error: lifetime may not live long enough
  --> /home/arthur/Git/rust/src/test/ui/nll/outlives-suggestion-simple.rs:41:9
   |
LL | impl<'a> Bar<'a> {
   |      -- lifetime `'a` defined here
LL |     pub fn get<'b>(&self) -> &'b usize {
   |                -- lifetime `'b` defined here
LL |         self.x //~ERROR lifetime may not live long enough
   |         ^^^^^^ associated function was supposed to return data with lifetime `'b` but it is returning data with lifetime `'a`
   |
   = help: consider adding the following bound: `'a: 'b`

error: lifetime may not live long enough
  --> /home/arthur/Git/rust/src/test/ui/nll/outlives-suggestion-simple.rs:52:9
   |
LL | impl<'a> Baz<'a> {
   |      -- lifetime `'a` defined here
LL |     fn get<'b>(&'b self) -> &'a i32 {
   |            -- lifetime `'b` defined here
LL |         self.x //~ERROR lifetime may not live long enough
   |         ^^^^^^ associated function was supposed to return data with lifetime `'a` but it is returning data with lifetime `'b`
   |
   = help: consider adding the following bound: `'b: 'a`

error: lifetime may not live long enough
  --> /home/arthur/Git/rust/src/test/ui/nll/outlives-suggestion-simple.rs:73:9
   |
LL | impl<'a> Foo2<'a> {
   |      -- lifetime `'a` defined here
LL |     // should not produce outlives suggestions to name 'self
LL |     fn get_bar(&self) -> Bar2 {
   |                - let's call the lifetime of this reference `'1`
LL |         Bar2::new(&self) //~ERROR lifetime may not live long enough
   |         ^^^^^^^^^^^^^^^^ argument requires that `'1` must outlive `'a`

error: aborting due to 10 previous errors
------------------------------------------


---- [ui (polonius)] ui/nll/user-annotations/closure-substs.rs stdout ----
diff of stderr:

6	...
7	LL |         return x;
8	   |                ^ returning this value requires that `'a` must outlive `'static`
-	   |
-	   = help: consider replacing `'a` with `'static`
11	
12	error: lifetime may not live long enough
13	  --> $DIR/closure-substs.rs:15:16

35	...
36	LL |         b(x);
37	   |         ^^^^ argument requires that `'a` must outlive `'static`
-	   |
-	   = help: consider replacing `'a` with `'static`
40	
41	error[E0521]: borrowed data escapes outside of closure
42	  --> $DIR/closure-substs.rs:29:9

43	   |
44	LL |     |x: &i32, b: fn(&'static i32)| {
-	   |      - `x` is a reference that is only valid in the closure body
+	   |      -  - let's call the lifetime of this reference `'1`
+	   |      |
+	   |      `x` is a reference that is only valid in the closure body
46	LL |         b(x);
-	   |         ^^^^ `x` escapes the closure body here
+	   |         ^^^^
+	   |         |
+	   |         `x` escapes the closure body here
+	   |         argument requires that `'1` must outlive `'static`
48	
49	error[E0521]: borrowed data escapes outside of closure
50	  --> $DIR/closure-substs.rs:29:9


The actual stderr differed from the expected stderr.
Actual stderr saved to /home/arthur/Git/rust/build/x86_64-unknown-linux-gnu/test/ui/nll/user-annotations/closure-substs.polonius/closure-substs.polonius.stderr
To update references, rerun the tests and pass the `--bless` flag
To only update this specific test, also pass `--test-args nll/user-annotations/closure-substs.rs`

error: 1 errors occurred comparing output.
status: exit status: 1
command: "/home/arthur/Git/rust/build/x86_64-unknown-linux-gnu/stage1/bin/rustc" "/home/arthur/Git/rust/src/test/ui/nll/user-annotations/closure-substs.rs" "-Zthreads=1" "--target=x86_64-unknown-linux-gnu" "--error-format" "json" "--json" "future-incompat" "-Ccodegen-units=1" "-Zui-testing" "-Zdeduplicate-diagnostics=no" "--emit" "metadata" "-C" "prefer-dynamic" "--out-dir" "/home/arthur/Git/rust/build/x86_64-unknown-linux-gnu/test/ui/nll/user-annotations/closure-substs.polonius" "-Zpolonius" "-Zborrowck=mir" "-A" "unused" "-Crpath" "-O" "-Cdebuginfo=0" "-Lnative=/home/arthur/Git/rust/build/x86_64-unknown-linux-gnu/native/rust-test-helpers" "-L" "/home/arthur/Git/rust/build/x86_64-unknown-linux-gnu/test/ui/nll/user-annotations/closure-substs.polonius/auxiliary"
stdout: none
--- stderr -------------------------------
error: lifetime may not live long enough
  --> /home/arthur/Git/rust/src/test/ui/nll/user-annotations/closure-substs.rs:8:16
   |
LL | fn foo<'a>() {
   |        -- lifetime `'a` defined here
...
LL |         return x; //~ ERROR lifetime may not live long enough
   |                ^ returning this value requires that `'a` must outlive `'static`

error: lifetime may not live long enough
  --> /home/arthur/Git/rust/src/test/ui/nll/user-annotations/closure-substs.rs:15:16
   |
LL |     |x: &i32| -> &'static i32 {
   |         - let's call the lifetime of this reference `'1`
LL |         return x; //~ ERROR lifetime may not live long enough
   |                ^ returning this value requires that `'1` must outlive `'static`

error: lifetime may not live long enough
  --> /home/arthur/Git/rust/src/test/ui/nll/user-annotations/closure-substs.rs:15:16
   |
LL |     |x: &i32| -> &'static i32 {
   |         -        - let's call the lifetime of this reference `'2`
   |         |
   |         let's call the lifetime of this reference `'1`
LL |         return x; //~ ERROR lifetime may not live long enough
   |                ^ returning this value requires that `'1` must outlive `'2`

error: lifetime may not live long enough
  --> /home/arthur/Git/rust/src/test/ui/nll/user-annotations/closure-substs.rs:22:9
   |
LL | fn bar<'a>() {
   |        -- lifetime `'a` defined here
...
LL |         b(x); //~ ERROR lifetime may not live long enough
   |         ^^^^ argument requires that `'a` must outlive `'static`

error[E0521]: borrowed data escapes outside of closure
  --> /home/arthur/Git/rust/src/test/ui/nll/user-annotations/closure-substs.rs:29:9
   |
LL |     |x: &i32, b: fn(&'static i32)| {
   |      -  - let's call the lifetime of this reference `'1`
   |      |
   |      `x` is a reference that is only valid in the closure body
LL |         b(x); //~ ERROR borrowed data escapes outside of closure
   |         ^^^^
   |         |
   |         `x` escapes the closure body here
   |         argument requires that `'1` must outlive `'static`

error[E0521]: borrowed data escapes outside of closure
  --> /home/arthur/Git/rust/src/test/ui/nll/user-annotations/closure-substs.rs:29:9
   |
LL |     |x: &i32, b: fn(&'static i32)| {
   |      -        - `b` declared here, outside of the closure body
   |      |
   |      `x` is a reference that is only valid in the closure body
LL |         b(x); //~ ERROR borrowed data escapes outside of closure
   |         ^^^^ `x` escapes the closure body here

error: aborting due to 6 previous errors

For more information about this error, try `rustc --explain E0521`.
------------------------------------------


---- [ui (polonius)] ui/regions/region-multiple-lifetime-bounds-on-fns-where-clause.rs stdout ----
diff of stderr:

60	
61	help: add bound `'b: 'a + 'c`
62	
-	error: higher-ranked subtype error
+	error[E0308]: mismatched types
64	  --> $DIR/region-multiple-lifetime-bounds-on-fns-where-clause.rs:22:12
65	   |
66	LL |     let _: fn(&mut &isize, &mut &isize, &mut &isize) = a;

-	   |            ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
+	   |            ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ one type is more general than the other
+	   |
+	   = note: expected fn pointer `for<'r, 's, 't0, 't1, 't2, 't3> fn(&'r mut &'s isize, &'t0 mut &'t1 isize, &'t2 mut &'t3 isize)`
+	              found fn pointer `for<'r, 's, 't0> fn(&'r mut &isize, &'s mut &isize, &'t0 mut &isize)`
68	
-	error: higher-ranked subtype error
+	error[E0308]: mismatched types
70	  --> $DIR/region-multiple-lifetime-bounds-on-fns-where-clause.rs:22:12
71	   |
72	LL |     let _: fn(&mut &isize, &mut &isize, &mut &isize) = a;

-	   |            ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
+	   |            ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ one type is more general than the other
+	   |
+	   = note: expected fn pointer `for<'r, 's, 't0, 't1, 't2, 't3> fn(&'r mut &'s isize, &'t0 mut &'t1 isize, &'t2 mut &'t3 isize)`
+	              found fn pointer `for<'r, 's, 't0> fn(&'r mut &isize, &'s mut &isize, &'t0 mut &isize)`
74	
-	error: higher-ranked subtype error
+	error[E0308]: mismatched types
76	  --> $DIR/region-multiple-lifetime-bounds-on-fns-where-clause.rs:22:12
77	   |
78	LL |     let _: fn(&mut &isize, &mut &isize, &mut &isize) = a;

-	   |            ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
+	   |            ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ one type is more general than the other
+	   |
+	   = note: expected fn pointer `for<'r, 's, 't0, 't1, 't2, 't3> fn(&'r mut &'s isize, &'t0 mut &'t1 isize, &'t2 mut &'t3 isize)`
+	              found fn pointer `for<'r, 's, 't0> fn(&'r mut &isize, &'s mut &isize, &'t0 mut &isize)`
80	
81	error: aborting due to 7 previous errors
82	

+	For more information about this error, try `rustc --explain E0308`.
83	


The actual stderr differed from the expected stderr.
Actual stderr saved to /home/arthur/Git/rust/build/x86_64-unknown-linux-gnu/test/ui/regions/region-multiple-lifetime-bounds-on-fns-where-clause.polonius/region-multiple-lifetime-bounds-on-fns-where-clause.polonius.stderr
To update references, rerun the tests and pass the `--bless` flag
To only update this specific test, also pass `--test-args regions/region-multiple-lifetime-bounds-on-fns-where-clause.rs`

error: 1 errors occurred comparing output.
status: exit status: 1
command: "/home/arthur/Git/rust/build/x86_64-unknown-linux-gnu/stage1/bin/rustc" "/home/arthur/Git/rust/src/test/ui/regions/region-multiple-lifetime-bounds-on-fns-where-clause.rs" "-Zthreads=1" "--target=x86_64-unknown-linux-gnu" "--error-format" "json" "--json" "future-incompat" "-Ccodegen-units=1" "-Zui-testing" "-Zdeduplicate-diagnostics=no" "--emit" "metadata" "-C" "prefer-dynamic" "--out-dir" "/home/arthur/Git/rust/build/x86_64-unknown-linux-gnu/test/ui/regions/region-multiple-lifetime-bounds-on-fns-where-clause.polonius" "-Zpolonius" "-Zborrowck=mir" "-A" "unused" "-Crpath" "-O" "-Cdebuginfo=0" "-Lnative=/home/arthur/Git/rust/build/x86_64-unknown-linux-gnu/native/rust-test-helpers" "-L" "/home/arthur/Git/rust/build/x86_64-unknown-linux-gnu/test/ui/regions/region-multiple-lifetime-bounds-on-fns-where-clause.polonius/auxiliary"
stdout: none
--- stderr -------------------------------
error: lifetime may not live long enough
  --> /home/arthur/Git/rust/src/test/ui/regions/region-multiple-lifetime-bounds-on-fns-where-clause.rs:9:5
   |
LL | fn b<'a, 'b, 'c>(x: &mut &'a isize, y: &mut &'b isize, z: &mut &'c isize) {
   |      --  -- lifetime `'b` defined here
   |      |
   |      lifetime `'a` defined here
LL |     // Illegal now because there is no `'b:'a` declaration.
LL |     *x = *y; //~ ERROR E0623
   |     ^^^^^^^ assignment requires that `'b` must outlive `'a`
   |
   = help: consider adding the following bound: `'b: 'a`

error: lifetime may not live long enough
  --> /home/arthur/Git/rust/src/test/ui/regions/region-multiple-lifetime-bounds-on-fns-where-clause.rs:10:5
   |
LL | fn b<'a, 'b, 'c>(x: &mut &'a isize, y: &mut &'b isize, z: &mut &'c isize) {
   |          --  -- lifetime `'c` defined here
   |          |
   |          lifetime `'b` defined here
...
LL |     *z = *y; //~ ERROR E0623
   |     ^^^^^^^ assignment requires that `'b` must outlive `'c`
   |
   = help: consider adding the following bound: `'b: 'c`

help: add bound `'b: 'a + 'c`

error: lifetime may not live long enough
  --> /home/arthur/Git/rust/src/test/ui/regions/region-multiple-lifetime-bounds-on-fns-where-clause.rs:16:5
   |
LL | fn c<'a,'b, 'c>(x: &mut &'a isize, y: &mut &'b isize, z: &mut &'c isize) {
   |      -- -- lifetime `'b` defined here
   |      |
   |      lifetime `'a` defined here
...
LL |     a(x, y, z); //~ ERROR lifetime mismatch [E0623]
   |     ^^^^^^^^^^ argument requires that `'b` must outlive `'a`
   |
   = help: consider adding the following bound: `'b: 'a`
   = note: requirement occurs because of a mutable reference to &isize
   = note: mutable references are invariant over their type parameter
   = help: see <https://doc.rust-lang.org/nomicon/subtyping.html> for more information about variance

error: lifetime may not live long enough
  --> /home/arthur/Git/rust/src/test/ui/regions/region-multiple-lifetime-bounds-on-fns-where-clause.rs:16:5
   |
LL | fn c<'a,'b, 'c>(x: &mut &'a isize, y: &mut &'b isize, z: &mut &'c isize) {
   |         --  -- lifetime `'c` defined here
   |         |
   |         lifetime `'b` defined here
...
LL |     a(x, y, z); //~ ERROR lifetime mismatch [E0623]
   |     ^^^^^^^^^^ argument requires that `'b` must outlive `'c`
   |
   = help: consider adding the following bound: `'b: 'c`
   = note: requirement occurs because of a mutable reference to &isize
   = note: mutable references are invariant over their type parameter
   = help: see <https://doc.rust-lang.org/nomicon/subtyping.html> for more information about variance

help: add bound `'b: 'a + 'c`

error[E0308]: mismatched types
  --> /home/arthur/Git/rust/src/test/ui/regions/region-multiple-lifetime-bounds-on-fns-where-clause.rs:22:12
   |
LL |     let _: fn(&mut &isize, &mut &isize, &mut &isize) = a; //~ ERROR E0308
   |            ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ one type is more general than the other
   |
   = note: expected fn pointer `for<'r, 's, 't0, 't1, 't2, 't3> fn(&'r mut &'s isize, &'t0 mut &'t1 isize, &'t2 mut &'t3 isize)`
              found fn pointer `for<'r, 's, 't0> fn(&'r mut &isize, &'s mut &isize, &'t0 mut &isize)`

error[E0308]: mismatched types
  --> /home/arthur/Git/rust/src/test/ui/regions/region-multiple-lifetime-bounds-on-fns-where-clause.rs:22:12
   |
LL |     let _: fn(&mut &isize, &mut &isize, &mut &isize) = a; //~ ERROR E0308
   |            ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ one type is more general than the other
   |
   = note: expected fn pointer `for<'r, 's, 't0, 't1, 't2, 't3> fn(&'r mut &'s isize, &'t0 mut &'t1 isize, &'t2 mut &'t3 isize)`
              found fn pointer `for<'r, 's, 't0> fn(&'r mut &isize, &'s mut &isize, &'t0 mut &isize)`

error[E0308]: mismatched types
  --> /home/arthur/Git/rust/src/test/ui/regions/region-multiple-lifetime-bounds-on-fns-where-clause.rs:22:12
   |
LL |     let _: fn(&mut &isize, &mut &isize, &mut &isize) = a; //~ ERROR E0308
   |            ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ one type is more general than the other
   |
   = note: expected fn pointer `for<'r, 's, 't0, 't1, 't2, 't3> fn(&'r mut &'s isize, &'t0 mut &'t1 isize, &'t2 mut &'t3 isize)`
              found fn pointer `for<'r, 's, 't0> fn(&'r mut &isize, &'s mut &isize, &'t0 mut &isize)`

error: aborting due to 7 previous errors

For more information about this error, try `rustc --explain E0308`.
------------------------------------------


---- [ui (polonius)] ui/regions/regions-assoc-type-in-supertrait-outlives-container.rs#migrate stdout ----
diff of stderr:

-	error[E0491]: in type `&'a WithAssoc<TheType<'b>>`, reference has a longer lifetime than the data it references
+	error: lifetime may not live long enough
2	  --> $DIR/regions-assoc-type-in-supertrait-outlives-container.rs:44:12
3	   |
+	LL | fn with_assoc<'a,'b>() {
+	   |               -- -- lifetime `'b` defined here
+	   |               |
+	   |               lifetime `'a` defined here
+	...
4	LL |     let _: &'a WithAssoc<TheType<'b>> = loop { };
-	   |            ^^^^^^^^^^^^^^^^^^^^^^^^^^
+	   |            ^^^^^^^^^^^^^^^^^^^^^^^^^^ type annotation requires that `'b` must outlive `'a`
6	   |
-	note: the pointer is valid for the lifetime `'a` as defined here
-	  --> $DIR/regions-assoc-type-in-supertrait-outlives-container.rs:38:15
-	   |
-	LL | fn with_assoc<'a,'b>() {
-	   |               ^^
-	note: but the referenced data is only valid for the lifetime `'b` as defined here
-	  --> $DIR/regions-assoc-type-in-supertrait-outlives-container.rs:38:18
-	   |
-	LL | fn with_assoc<'a,'b>() {
-	   |                  ^^
+	   = help: consider adding the following bound: `'b: 'a`
17	
18	error: aborting due to previous error
19	

-	For more information about this error, try `rustc --explain E0491`.
21	


The actual stderr differed from the expected stderr.
Actual stderr saved to /home/arthur/Git/rust/build/x86_64-unknown-linux-gnu/test/ui/regions/regions-assoc-type-in-supertrait-outlives-container.migrate.polonius/regions-assoc-type-in-supertrait-outlives-container.migrate.polonius.stderr
To update references, rerun the tests and pass the `--bless` flag
To only update this specific test, also pass `--test-args regions/regions-assoc-type-in-supertrait-outlives-container.rs`

error in revision `migrate`: 1 errors occurred comparing output.
status: exit status: 1
command: "/home/arthur/Git/rust/build/x86_64-unknown-linux-gnu/stage1/bin/rustc" "/home/arthur/Git/rust/src/test/ui/regions/regions-assoc-type-in-supertrait-outlives-container.rs" "-Zthreads=1" "--target=x86_64-unknown-linux-gnu" "--cfg" "migrate" "--error-format" "json" "--json" "future-incompat" "-Ccodegen-units=1" "-Zui-testing" "-Zdeduplicate-diagnostics=no" "--emit" "metadata" "-C" "prefer-dynamic" "--out-dir" "/home/arthur/Git/rust/build/x86_64-unknown-linux-gnu/test/ui/regions/regions-assoc-type-in-supertrait-outlives-container.migrate.polonius" "-Zpolonius" "-Zborrowck=mir" "-A" "unused" "-Crpath" "-O" "-Cdebuginfo=0" "-Lnative=/home/arthur/Git/rust/build/x86_64-unknown-linux-gnu/native/rust-test-helpers" "-L" "/home/arthur/Git/rust/build/x86_64-unknown-linux-gnu/test/ui/regions/regions-assoc-type-in-supertrait-outlives-container.migrate.polonius/auxiliary"
stdout: none
--- stderr -------------------------------
error: lifetime may not live long enough
  --> /home/arthur/Git/rust/src/test/ui/regions/regions-assoc-type-in-supertrait-outlives-container.rs:44:12
   |
LL | fn with_assoc<'a,'b>() {
   |               -- -- lifetime `'b` defined here
   |               |
   |               lifetime `'a` defined here
...
LL |     let _: &'a WithAssoc<TheType<'b>> = loop { };
   |            ^^^^^^^^^^^^^^^^^^^^^^^^^^ type annotation requires that `'b` must outlive `'a`
   |
   = help: consider adding the following bound: `'b: 'a`

error: aborting due to previous error
------------------------------------------


---- [ui (polonius)] ui/regions/regions-free-region-ordering-caller.rs#migrate stdout ----
diff of stderr:

-	error[E0491]: in type `&'b &'a usize`, reference has a longer lifetime than the data it references
+	error: lifetime may not live long enough
2	  --> $DIR/regions-free-region-ordering-caller.rs:16:12
3	   |
+	LL | fn call2<'a, 'b>(a: &'a usize, b: &'b usize) {
+	   |          --  -- lifetime `'b` defined here
+	   |          |
+	   |          lifetime `'a` defined here
4	LL |     let z: Option<&'b &'a usize> = None;
-	   |            ^^^^^^^^^^^^^^^^^^^^^
+	   |            ^^^^^^^^^^^^^^^^^^^^^ type annotation requires that `'a` must outlive `'b`
6	   |
-	note: the pointer is valid for the lifetime `'b` as defined here
-	  --> $DIR/regions-free-region-ordering-caller.rs:15:14
-	   |
-	LL | fn call2<'a, 'b>(a: &'a usize, b: &'b usize) {
-	   |              ^^
-	note: but the referenced data is only valid for the lifetime `'a` as defined here
-	  --> $DIR/regions-free-region-ordering-caller.rs:15:10
-	   |
-	LL | fn call2<'a, 'b>(a: &'a usize, b: &'b usize) {
-	   |          ^^
+	   = help: consider adding the following bound: `'a: 'b`
17	
-	error[E0491]: in type `&'b Paramd<'a>`, reference has a longer lifetime than the data it references
+	error: lifetime may not live long enough
19	  --> $DIR/regions-free-region-ordering-caller.rs:22:12
20	   |
+	LL | fn call3<'a, 'b>(a: &'a usize, b: &'b usize) {
+	   |          --  -- lifetime `'b` defined here
+	   |          |
+	   |          lifetime `'a` defined here
+	LL |     let y: Paramd<'a> = Paramd { x: a };
21	LL |     let z: Option<&'b Paramd<'a>> = None;
-	   |            ^^^^^^^^^^^^^^^^^^^^^^
+	   |            ^^^^^^^^^^^^^^^^^^^^^^ type annotation requires that `'a` must outlive `'b`
23	   |
-	note: the pointer is valid for the lifetime `'b` as defined here
-	  --> $DIR/regions-free-region-ordering-caller.rs:20:14
-	   |
-	LL | fn call3<'a, 'b>(a: &'a usize, b: &'b usize) {
-	   |              ^^
-	note: but the referenced data is only valid for the lifetime `'a` as defined here
-	  --> $DIR/regions-free-region-ordering-caller.rs:20:10
-	   |
-	LL | fn call3<'a, 'b>(a: &'a usize, b: &'b usize) {
-	   |          ^^
+	   = help: consider adding the following bound: `'a: 'b`
34	
-	error[E0491]: in type `&'a &'b usize`, reference has a longer lifetime than the data it references
+	error: lifetime may not live long enough
36	  --> $DIR/regions-free-region-ordering-caller.rs:27:12
37	   |
+	LL | fn call4<'a, 'b>(a: &'a usize, b: &'b usize) {
+	   |          --  -- lifetime `'b` defined here
+	   |          |
+	   |          lifetime `'a` defined here
38	LL |     let z: Option<&'a &'b usize> = None;
-	   |            ^^^^^^^^^^^^^^^^^^^^^
+	   |            ^^^^^^^^^^^^^^^^^^^^^ type annotation requires that `'b` must outlive `'a`
40	   |
-	note: the pointer is valid for the lifetime `'a` as defined here
-	  --> $DIR/regions-free-region-ordering-caller.rs:26:10
-	   |
-	LL | fn call4<'a, 'b>(a: &'a usize, b: &'b usize) {
-	   |          ^^
-	note: but the referenced data is only valid for the lifetime `'b` as defined here
-	  --> $DIR/regions-free-region-ordering-caller.rs:26:14
-	   |
-	LL | fn call4<'a, 'b>(a: &'a usize, b: &'b usize) {
-	   |              ^^
+	   = help: consider adding the following bound: `'b: 'a`
51	
52	error: aborting due to 3 previous errors
53	

-	For more information about this error, try `rustc --explain E0491`.
55	


The actual stderr differed from the expected stderr.
Actual stderr saved to /home/arthur/Git/rust/build/x86_64-unknown-linux-gnu/test/ui/regions/regions-free-region-ordering-caller.migrate.polonius/regions-free-region-ordering-caller.migrate.polonius.stderr
To update references, rerun the tests and pass the `--bless` flag
To only update this specific test, also pass `--test-args regions/regions-free-region-ordering-caller.rs`

error in revision `migrate`: 1 errors occurred comparing output.
status: exit status: 1
command: "/home/arthur/Git/rust/build/x86_64-unknown-linux-gnu/stage1/bin/rustc" "/home/arthur/Git/rust/src/test/ui/regions/regions-free-region-ordering-caller.rs" "-Zthreads=1" "--target=x86_64-unknown-linux-gnu" "--cfg" "migrate" "--error-format" "json" "--json" "future-incompat" "-Ccodegen-units=1" "-Zui-testing" "-Zdeduplicate-diagnostics=no" "--emit" "metadata" "-C" "prefer-dynamic" "--out-dir" "/home/arthur/Git/rust/build/x86_64-unknown-linux-gnu/test/ui/regions/regions-free-region-ordering-caller.migrate.polonius" "-Zpolonius" "-Zborrowck=mir" "-A" "unused" "-Crpath" "-O" "-Cdebuginfo=0" "-Lnative=/home/arthur/Git/rust/build/x86_64-unknown-linux-gnu/native/rust-test-helpers" "-L" "/home/arthur/Git/rust/build/x86_64-unknown-linux-gnu/test/ui/regions/regions-free-region-ordering-caller.migrate.polonius/auxiliary"
stdout: none
--- stderr -------------------------------
error: lifetime may not live long enough
  --> /home/arthur/Git/rust/src/test/ui/regions/regions-free-region-ordering-caller.rs:16:12
   |
LL | fn call2<'a, 'b>(a: &'a usize, b: &'b usize) {
   |          --  -- lifetime `'b` defined here
   |          |
   |          lifetime `'a` defined here
LL |     let z: Option<&'b &'a usize> = None;//[migrate]~ ERROR E0491
   |            ^^^^^^^^^^^^^^^^^^^^^ type annotation requires that `'a` must outlive `'b`
   |
   = help: consider adding the following bound: `'a: 'b`

error: lifetime may not live long enough
  --> /home/arthur/Git/rust/src/test/ui/regions/regions-free-region-ordering-caller.rs:22:12
   |
LL | fn call3<'a, 'b>(a: &'a usize, b: &'b usize) {
   |          --  -- lifetime `'b` defined here
   |          |
   |          lifetime `'a` defined here
LL |     let y: Paramd<'a> = Paramd { x: a };
LL |     let z: Option<&'b Paramd<'a>> = None;//[migrate]~ ERROR E0491
   |            ^^^^^^^^^^^^^^^^^^^^^^ type annotation requires that `'a` must outlive `'b`
   |
   = help: consider adding the following bound: `'a: 'b`

error: lifetime may not live long enough
  --> /home/arthur/Git/rust/src/test/ui/regions/regions-free-region-ordering-caller.rs:27:12
   |
LL | fn call4<'a, 'b>(a: &'a usize, b: &'b usize) {
   |          --  -- lifetime `'b` defined here
   |          |
   |          lifetime `'a` defined here
LL |     let z: Option<&'a &'b usize> = None;//[migrate]~ ERROR E0491
   |            ^^^^^^^^^^^^^^^^^^^^^ type annotation requires that `'b` must outlive `'a`
   |
   = help: consider adding the following bound: `'b: 'a`

error: aborting due to 3 previous errors
------------------------------------------


---- [ui (polonius)] ui/regions/regions-outlives-projection-container-hrtb.rs#migrate stdout ----
diff of stderr:

-	error[E0491]: in type `&'a WithHrAssoc<TheType<'b>>`, reference has a longer lifetime than the data it references
+	error: lifetime may not live long enough
2	  --> $DIR/regions-outlives-projection-container-hrtb.rs:35:12
3	   |
+	LL | fn with_assoc<'a,'b>() {
+	   |               -- -- lifetime `'b` defined here
+	   |               |
+	   |               lifetime `'a` defined here
+	...
4	LL |     let _: &'a WithHrAssoc<TheType<'b>> = loop { };
-	   |            ^^^^^^^^^^^^^^^^^^^^^^^^^^^^
+	   |            ^^^^^^^^^^^^^^^^^^^^^^^^^^^^ type annotation requires that `'b` must outlive `'a`
6	   |
-	note: the pointer is valid for the lifetime `'a` as defined here
-	  --> $DIR/regions-outlives-projection-container-hrtb.rs:32:15
-	   |
-	LL | fn with_assoc<'a,'b>() {
-	   |               ^^
-	note: but the referenced data is only valid for the lifetime `'b` as defined here
-	  --> $DIR/regions-outlives-projection-container-hrtb.rs:32:18
-	   |
-	LL | fn with_assoc<'a,'b>() {
-	   |                  ^^
+	   = help: consider adding the following bound: `'b: 'a`
17	
-	error[E0491]: in type `&'a WithHrAssocSub<TheType<'b>>`, reference has a longer lifetime than the data it references
+	error: lifetime may not live long enough
19	  --> $DIR/regions-outlives-projection-container-hrtb.rs:55:12
20	   |
+	LL | fn with_assoc_sub<'a,'b>() {
+	   |                   -- -- lifetime `'b` defined here
+	   |                   |
+	   |                   lifetime `'a` defined here
+	...
21	LL |     let _: &'a WithHrAssocSub<TheType<'b>> = loop { };
-	   |            ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
+	   |            ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ type annotation requires that `'b` must outlive `'a`
23	   |
-	note: the pointer is valid for the lifetime `'a` as defined here
-	  --> $DIR/regions-outlives-projection-container-hrtb.rs:51:19
-	   |
-	LL | fn with_assoc_sub<'a,'b>() {
-	   |                   ^^
-	note: but the referenced data is only valid for the lifetime `'b` as defined here
-	  --> $DIR/regions-outlives-projection-container-hrtb.rs:51:22
-	   |
-	LL | fn with_assoc_sub<'a,'b>() {
-	   |                      ^^
+	   = help: consider adding the following bound: `'b: 'a`
34	
35	error: aborting due to 2 previous errors
36	

-	For more information about this error, try `rustc --explain E0491`.
38	


The actual stderr differed from the expected stderr.
Actual stderr saved to /home/arthur/Git/rust/build/x86_64-unknown-linux-gnu/test/ui/regions/regions-outlives-projection-container-hrtb.migrate.polonius/regions-outlives-projection-container-hrtb.migrate.polonius.stderr
To update references, rerun the tests and pass the `--bless` flag
To only update this specific test, also pass `--test-args regions/regions-outlives-projection-container-hrtb.rs`

error in revision `migrate`: 1 errors occurred comparing output.
status: exit status: 1
command: "/home/arthur/Git/rust/build/x86_64-unknown-linux-gnu/stage1/bin/rustc" "/home/arthur/Git/rust/src/test/ui/regions/regions-outlives-projection-container-hrtb.rs" "-Zthreads=1" "--target=x86_64-unknown-linux-gnu" "--cfg" "migrate" "--error-format" "json" "--json" "future-incompat" "-Ccodegen-units=1" "-Zui-testing" "-Zdeduplicate-diagnostics=no" "--emit" "metadata" "-C" "prefer-dynamic" "--out-dir" "/home/arthur/Git/rust/build/x86_64-unknown-linux-gnu/test/ui/regions/regions-outlives-projection-container-hrtb.migrate.polonius" "-Zpolonius" "-Zborrowck=mir" "-A" "unused" "-Crpath" "-O" "-Cdebuginfo=0" "-Lnative=/home/arthur/Git/rust/build/x86_64-unknown-linux-gnu/native/rust-test-helpers" "-L" "/home/arthur/Git/rust/build/x86_64-unknown-linux-gnu/test/ui/regions/regions-outlives-projection-container-hrtb.migrate.polonius/auxiliary"
stdout: none
--- stderr -------------------------------
error: lifetime may not live long enough
  --> /home/arthur/Git/rust/src/test/ui/regions/regions-outlives-projection-container-hrtb.rs:35:12
   |
LL | fn with_assoc<'a,'b>() {
   |               -- -- lifetime `'b` defined here
   |               |
   |               lifetime `'a` defined here
...
LL |     let _: &'a WithHrAssoc<TheType<'b>> = loop { };
   |            ^^^^^^^^^^^^^^^^^^^^^^^^^^^^ type annotation requires that `'b` must outlive `'a`
   |
   = help: consider adding the following bound: `'b: 'a`

error: lifetime may not live long enough
  --> /home/arthur/Git/rust/src/test/ui/regions/regions-outlives-projection-container-hrtb.rs:55:12
   |
LL | fn with_assoc_sub<'a,'b>() {
   |                   -- -- lifetime `'b` defined here
   |                   |
   |                   lifetime `'a` defined here
...
LL |     let _: &'a WithHrAssocSub<TheType<'b>> = loop { };
   |            ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ type annotation requires that `'b` must outlive `'a`
   |
   = help: consider adding the following bound: `'b: 'a`

error: aborting due to 2 previous errors
------------------------------------------


---- [ui (polonius)] ui/regions/regions-outlives-projection-container-wc.rs#migrate stdout ----
diff of stderr:

-	error[E0491]: in type `&'a WithAssoc<TheType<'b>>`, reference has a longer lifetime than the data it references
+	error: lifetime may not live long enough
2	  --> $DIR/regions-outlives-projection-container-wc.rs:38:12
3	   |
+	LL | fn with_assoc<'a,'b>() {
+	   |               -- -- lifetime `'b` defined here
+	   |               |
+	   |               lifetime `'a` defined here
+	...
4	LL |     let _: &'a WithAssoc<TheType<'b>> = loop { };
-	   |            ^^^^^^^^^^^^^^^^^^^^^^^^^^
+	   |            ^^^^^^^^^^^^^^^^^^^^^^^^^^ type annotation requires that `'b` must outlive `'a`
6	   |
-	note: the pointer is valid for the lifetime `'a` as defined here
-	  --> $DIR/regions-outlives-projection-container-wc.rs:32:15
-	   |
-	LL | fn with_assoc<'a,'b>() {
-	   |               ^^
-	note: but the referenced data is only valid for the lifetime `'b` as defined here
-	  --> $DIR/regions-outlives-projection-container-wc.rs:32:18
-	   |
-	LL | fn with_assoc<'a,'b>() {
-	   |                  ^^
+	   = help: consider adding the following bound: `'b: 'a`
17	
18	error: aborting due to previous error
19	

-	For more information about this error, try `rustc --explain E0491`.
21	


The actual stderr differed from the expected stderr.
Actual stderr saved to /home/arthur/Git/rust/build/x86_64-unknown-linux-gnu/test/ui/regions/regions-outlives-projection-container-wc.migrate.polonius/regions-outlives-projection-container-wc.migrate.polonius.stderr
To update references, rerun the tests and pass the `--bless` flag
To only update this specific test, also pass `--test-args regions/regions-outlives-projection-container-wc.rs`

error in revision `migrate`: 1 errors occurred comparing output.
status: exit status: 1
command: "/home/arthur/Git/rust/build/x86_64-unknown-linux-gnu/stage1/bin/rustc" "/home/arthur/Git/rust/src/test/ui/regions/regions-outlives-projection-container-wc.rs" "-Zthreads=1" "--target=x86_64-unknown-linux-gnu" "--cfg" "migrate" "--error-format" "json" "--json" "future-incompat" "-Ccodegen-units=1" "-Zui-testing" "-Zdeduplicate-diagnostics=no" "--emit" "metadata" "-C" "prefer-dynamic" "--out-dir" "/home/arthur/Git/rust/build/x86_64-unknown-linux-gnu/test/ui/regions/regions-outlives-projection-container-wc.migrate.polonius" "-Zpolonius" "-Zborrowck=mir" "-A" "unused" "-Crpath" "-O" "-Cdebuginfo=0" "-Lnative=/home/arthur/Git/rust/build/x86_64-unknown-linux-gnu/native/rust-test-helpers" "-L" "/home/arthur/Git/rust/build/x86_64-unknown-linux-gnu/test/ui/regions/regions-outlives-projection-container-wc.migrate.polonius/auxiliary"
stdout: none
--- stderr -------------------------------
error: lifetime may not live long enough
  --> /home/arthur/Git/rust/src/test/ui/regions/regions-outlives-projection-container-wc.rs:38:12
   |
LL | fn with_assoc<'a,'b>() {
   |               -- -- lifetime `'b` defined here
   |               |
   |               lifetime `'a` defined here
...
LL |     let _: &'a WithAssoc<TheType<'b>> = loop { };
   |            ^^^^^^^^^^^^^^^^^^^^^^^^^^ type annotation requires that `'b` must outlive `'a`
   |
   = help: consider adding the following bound: `'b: 'a`

error: aborting due to previous error
------------------------------------------


---- [ui (polonius)] ui/numbers-arithmetic/saturating-float-casts.rs stdout ----

error: test compilation failed although it shouldn't!
status: signal: 9
command: "/home/arthur/Git/rust/build/x86_64-unknown-linux-gnu/stage1/bin/rustc" "/home/arthur/Git/rust/src/test/ui/numbers-arithmetic/saturating-float-casts.rs" "-Zthreads=1" "--target=x86_64-unknown-linux-gnu" "--error-format" "json" "--json" "future-incompat" "-Ccodegen-units=1" "-Zui-testing" "-Zdeduplicate-diagnostics=no" "-C" "prefer-dynamic" "-o" "/home/arthur/Git/rust/build/x86_64-unknown-linux-gnu/test/ui/numbers-arithmetic/saturating-float-casts.polonius/a" "-Zpolonius" "-Zborrowck=mir" "-Crpath" "-O" "-Cdebuginfo=0" "-Lnative=/home/arthur/Git/rust/build/x86_64-unknown-linux-gnu/native/rust-test-helpers" "-Zmir-opt-level=0" "-L" "/home/arthur/Git/rust/build/x86_64-unknown-linux-gnu/test/ui/numbers-arithmetic/saturating-float-casts.polonius/auxiliary"
stdout: none
stderr: none


---- [ui (polonius)] ui/traits/trait-upcasting/type-checking-test-3.rs stdout ----
diff of stderr:

5	   |                -- lifetime `'a` defined here
6	LL |     let _ = x as &dyn Bar<'a>; // Error
7	   |             ^^^^^^^^^^^^^^^^^ type annotation requires that `'a` must outlive `'static`
-	   |
-	   = help: consider replacing `'a` with `'static`
10	
11	error: lifetime may not live long enough
12	  --> $DIR/type-checking-test-3.rs:18:13

15	   |                -- lifetime `'a` defined here
16	LL |     let _ = x as &dyn Bar<'static>; // Error
17	   |             ^^^^^^^^^^^^^^^^^^^^^^ type annotation requires that `'a` must outlive `'static`
-	   |
-	   = help: consider replacing `'a` with `'static`
20	
21	error: aborting due to 2 previous errors
22	


The actual stderr differed from the expected stderr.
Actual stderr saved to /home/arthur/Git/rust/build/x86_64-unknown-linux-gnu/test/ui/traits/trait-upcasting/type-checking-test-3.polonius/type-checking-test-3.polonius.stderr
To update references, rerun the tests and pass the `--bless` flag
To only update this specific test, also pass `--test-args traits/trait-upcasting/type-checking-test-3.rs`

error: 1 errors occurred comparing output.
status: exit status: 1
command: "/home/arthur/Git/rust/build/x86_64-unknown-linux-gnu/stage1/bin/rustc" "/home/arthur/Git/rust/src/test/ui/traits/trait-upcasting/type-checking-test-3.rs" "-Zthreads=1" "--target=x86_64-unknown-linux-gnu" "--error-format" "json" "--json" "future-incompat" "-Ccodegen-units=1" "-Zui-testing" "-Zdeduplicate-diagnostics=no" "--emit" "metadata" "-C" "prefer-dynamic" "--out-dir" "/home/arthur/Git/rust/build/x86_64-unknown-linux-gnu/test/ui/traits/trait-upcasting/type-checking-test-3.polonius" "-Zpolonius" "-Zborrowck=mir" "-A" "unused" "-Crpath" "-O" "-Cdebuginfo=0" "-Lnative=/home/arthur/Git/rust/build/x86_64-unknown-linux-gnu/native/rust-test-helpers" "-L" "/home/arthur/Git/rust/build/x86_64-unknown-linux-gnu/test/ui/traits/trait-upcasting/type-checking-test-3.polonius/auxiliary"
stdout: none
--- stderr -------------------------------
error: lifetime may not live long enough
  --> /home/arthur/Git/rust/src/test/ui/traits/trait-upcasting/type-checking-test-3.rs:13:13
   |
LL | fn test_wrong1<'a>(x: &dyn Foo<'static>, y: &'a u32) {
   |                -- lifetime `'a` defined here
LL |     let _ = x as &dyn Bar<'a>; // Error
   |             ^^^^^^^^^^^^^^^^^ type annotation requires that `'a` must outlive `'static`

error: lifetime may not live long enough
  --> /home/arthur/Git/rust/src/test/ui/traits/trait-upcasting/type-checking-test-3.rs:18:13
   |
LL | fn test_wrong2<'a>(x: &dyn Foo<'a>) {
   |                -- lifetime `'a` defined here
LL |     let _ = x as &dyn Bar<'static>; // Error
   |             ^^^^^^^^^^^^^^^^^^^^^^ type annotation requires that `'a` must outlive `'static`

error: aborting due to 2 previous errors
------------------------------------------


---- [ui (polonius)] ui/traits/trait-upcasting/type-checking-test-4.rs stdout ----
diff of stderr:

5	   |                -- lifetime `'a` defined here
6	LL |     let _ = x as &dyn Bar<'static, 'a>; // Error
7	   |             ^^^^^^^^^^^^^^^^^^^^^^^^^^ type annotation requires that `'a` must outlive `'static`
-	   |
-	   = help: consider replacing `'a` with `'static`
10	
11	error: lifetime may not live long enough
12	  --> $DIR/type-checking-test-4.rs:22:13

15	   |                -- lifetime `'a` defined here
16	LL |     let _ = x as &dyn Bar<'a, 'static>; // Error
17	   |             ^^^^^^^^^^^^^^^^^^^^^^^^^^ type annotation requires that `'a` must outlive `'static`
-	   |
-	   = help: consider replacing `'a` with `'static`
20	
21	error: lifetime may not live long enough
22	  --> $DIR/type-checking-test-4.rs:29:5

26	...
27	LL |     y.get_b() // ERROR
28	   |     ^^^^^^^^^ returning this value requires that `'a` must outlive `'static`
+	
+	error: lifetime may not live long enough
+	  --> $DIR/type-checking-test-4.rs:33:5
29	   |
-	   = help: consider replacing `'a` with `'static`
+	LL | fn test_wrong4<'a>(x: &dyn Foo<'a>) -> Option<&'static u32> {
+	   |                -- lifetime `'a` defined here
+	LL |     <_ as Bar>::get_b(x) // ERROR
+	   |     ^^^^^^^^^^^^^^^^^^^^ returning this value requires that `'a` must outlive `'static`
31	
-	error: aborting due to 3 previous errors
+	error: lifetime may not live long enough
+	  --> $DIR/type-checking-test-4.rs:38:5
+	   |
+	LL | fn test_wrong5<'a>(x: &dyn Foo<'a>) -> Option<&'static u32> {
+	   |                -- lifetime `'a` defined here
+	LL |     <_ as Bar<'_, '_>>::get_b(x) // ERROR
+	   |     ^^^^^^^^^^^^^^^^^^^^^^^^^^^^ returning this value requires that `'a` must outlive `'static`
+	
+	error: lifetime may not live long enough
+	  --> $DIR/type-checking-test-4.rs:47:5
+	   |
+	LL | fn test_wrong6<'a>(x: &dyn Foo<'a>) -> Option<&'static u32> {
+	   |                -- lifetime `'a` defined here
+	...
+	LL |     z.get_b() // ERROR
+	   |     ^^^^^^^^^ returning this value requires that `'a` must outlive `'static`
+	
+	error: aborting due to 6 previous errors
33	
34	


The actual stderr differed from the expected stderr.
Actual stderr saved to /home/arthur/Git/rust/build/x86_64-unknown-linux-gnu/test/ui/traits/trait-upcasting/type-checking-test-4.polonius/type-checking-test-4.polonius.stderr
To update references, rerun the tests and pass the `--bless` flag
To only update this specific test, also pass `--test-args traits/trait-upcasting/type-checking-test-4.rs`

error: 1 errors occurred comparing output.
status: exit status: 1
command: "/home/arthur/Git/rust/build/x86_64-unknown-linux-gnu/stage1/bin/rustc" "/home/arthur/Git/rust/src/test/ui/traits/trait-upcasting/type-checking-test-4.rs" "-Zthreads=1" "--target=x86_64-unknown-linux-gnu" "--error-format" "json" "--json" "future-incompat" "-Ccodegen-units=1" "-Zui-testing" "-Zdeduplicate-diagnostics=no" "--emit" "metadata" "-C" "prefer-dynamic" "--out-dir" "/home/arthur/Git/rust/build/x86_64-unknown-linux-gnu/test/ui/traits/trait-upcasting/type-checking-test-4.polonius" "-Zpolonius" "-Zborrowck=mir" "-A" "unused" "-Crpath" "-O" "-Cdebuginfo=0" "-Lnative=/home/arthur/Git/rust/build/x86_64-unknown-linux-gnu/native/rust-test-helpers" "-L" "/home/arthur/Git/rust/build/x86_64-unknown-linux-gnu/test/ui/traits/trait-upcasting/type-checking-test-4.polonius/auxiliary"
stdout: none
--- stderr -------------------------------
error: lifetime may not live long enough
  --> /home/arthur/Git/rust/src/test/ui/traits/trait-upcasting/type-checking-test-4.rs:17:13
   |
LL | fn test_wrong1<'a>(x: &dyn Foo<'static>, y: &'a u32) {
   |                -- lifetime `'a` defined here
LL |     let _ = x as &dyn Bar<'static, 'a>; // Error
   |             ^^^^^^^^^^^^^^^^^^^^^^^^^^ type annotation requires that `'a` must outlive `'static`

error: lifetime may not live long enough
  --> /home/arthur/Git/rust/src/test/ui/traits/trait-upcasting/type-checking-test-4.rs:22:13
   |
LL | fn test_wrong2<'a>(x: &dyn Foo<'static>, y: &'a u32) {
   |                -- lifetime `'a` defined here
LL |     let _ = x as &dyn Bar<'a, 'static>; // Error
   |             ^^^^^^^^^^^^^^^^^^^^^^^^^^ type annotation requires that `'a` must outlive `'static`

error: lifetime may not live long enough
  --> /home/arthur/Git/rust/src/test/ui/traits/trait-upcasting/type-checking-test-4.rs:29:5
   |
LL | fn test_wrong3<'a>(x: &dyn Foo<'a>) -> Option<&'static u32> {
   |                -- lifetime `'a` defined here
...
LL |     y.get_b() // ERROR
   |     ^^^^^^^^^ returning this value requires that `'a` must outlive `'static`

error: lifetime may not live long enough
  --> /home/arthur/Git/rust/src/test/ui/traits/trait-upcasting/type-checking-test-4.rs:33:5
   |
LL | fn test_wrong4<'a>(x: &dyn Foo<'a>) -> Option<&'static u32> {
   |                -- lifetime `'a` defined here
LL |     <_ as Bar>::get_b(x) // ERROR
   |     ^^^^^^^^^^^^^^^^^^^^ returning this value requires that `'a` must outlive `'static`

error: lifetime may not live long enough
  --> /home/arthur/Git/rust/src/test/ui/traits/trait-upcasting/type-checking-test-4.rs:38:5
   |
LL | fn test_wrong5<'a>(x: &dyn Foo<'a>) -> Option<&'static u32> {
   |                -- lifetime `'a` defined here
LL |     <_ as Bar<'_, '_>>::get_b(x) // ERROR
   |     ^^^^^^^^^^^^^^^^^^^^^^^^^^^^ returning this value requires that `'a` must outlive `'static`

error: lifetime may not live long enough
  --> /home/arthur/Git/rust/src/test/ui/traits/trait-upcasting/type-checking-test-4.rs:47:5
   |
LL | fn test_wrong6<'a>(x: &dyn Foo<'a>) -> Option<&'static u32> {
   |                -- lifetime `'a` defined here
...
LL |     z.get_b() // ERROR
   |     ^^^^^^^^^ returning this value requires that `'a` must outlive `'static`

error: aborting due to 6 previous errors
------------------------------------------


---- [ui (polonius)] ui/issues/issue-74564-if-expr-stack-overflow.rs stdout ----

error: test compilation failed although it shouldn't!
status: signal: 9
command: "/home/arthur/Git/rust/build/x86_64-unknown-linux-gnu/stage1/bin/rustc" "/home/arthur/Git/rust/src/test/ui/issues/issue-74564-if-expr-stack-overflow.rs" "-Zthreads=1" "--target=x86_64-unknown-linux-gnu" "--error-format" "json" "--json" "future-incompat" "-Ccodegen-units=1" "-Zui-testing" "-Zdeduplicate-diagnostics=no" "-C" "prefer-dynamic" "--out-dir" "/home/arthur/Git/rust/build/x86_64-unknown-linux-gnu/test/ui/issues/issue-74564-if-expr-stack-overflow.polonius" "-Zpolonius" "-Zborrowck=mir" "-A" "unused" "-Crpath" "-O" "-Cdebuginfo=0" "-Lnative=/home/arthur/Git/rust/build/x86_64-unknown-linux-gnu/native/rust-test-helpers" "-L" "/home/arthur/Git/rust/build/x86_64-unknown-linux-gnu/test/ui/issues/issue-74564-if-expr-stack-overflow.polonius/auxiliary"
stdout: none
stderr: none



failures:
    [ui (polonius)] ui/closures/closure-expected-type/expect-region-supply-region-2.rs
    [ui (polonius)] ui/crate-loading/crateresolve1.rs
    [ui (polonius)] ui/crate-loading/crateresolve2.rs
    [ui (polonius)] ui/error-codes/E0464.rs
    [ui (polonius)] ui/generic-associated-types/issue-91139.rs#migrate
    [ui (polonius)] ui/generic-associated-types/issue-92096.rs#migrate
    [ui (polonius)] ui/higher-rank-trait-bounds/normalize-under-binder/issue-71955.rs#migrate
    [ui (polonius)] ui/hrtb/hrtb-just-for-static.rs
    [ui (polonius)] ui/hrtb/hrtb-perfect-forwarding.rs
    [ui (polonius)] ui/impl-trait/multiple-lifetimes/error-handling.rs
    [ui (polonius)] ui/issues/issue-26217.rs
    [ui (polonius)] ui/issues/issue-74564-if-expr-stack-overflow.rs
    [ui (polonius)] ui/nll/get_default.rs
    [ui (polonius)] ui/nll/lint-no-err.rs
    [ui (polonius)] ui/nll/outlives-suggestion-simple.rs
    [ui (polonius)] ui/nll/user-annotations/closure-substs.rs
    [ui (polonius)] ui/numbers-arithmetic/saturating-float-casts.rs
    [ui (polonius)] ui/regions/region-multiple-lifetime-bounds-on-fns-where-clause.rs
    [ui (polonius)] ui/regions/regions-assoc-type-in-supertrait-outlives-container.rs#migrate
    [ui (polonius)] ui/regions/regions-free-region-ordering-caller.rs#migrate
    [ui (polonius)] ui/regions/regions-outlives-projection-container-hrtb.rs#migrate
    [ui (polonius)] ui/regions/regions-outlives-projection-container-wc.rs#migrate
    [ui (polonius)] ui/traits/trait-upcasting/type-checking-test-3.rs
    [ui (polonius)] ui/traits/trait-upcasting/type-checking-test-4.rs

test result: FAILED. 12588 passed; 24 failed; 120 ignored; 0 measured; 0 filtered out; finished in 2156.02s

Some tests failed in compiletest suite=ui compare_mode=Polonius mode=ui host=x86_64-unknown-linux-gnu target=x86_64-unknown-linux-gnu
```
