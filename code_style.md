# Lux - Code style
  * syntax
    * types use `PascalCase`
    * identifiers use `snake_case`
    * constants use `SCREAMING_SNAKE_CASE`
    * identifiers (variable names etc.) should make sense
      * don't hesitate to shorten identifiers that are known from the context
        * e.g. `vertex` to `vert` in a rendering function
          * `i`, `j` and similar are allowed in (non-range-based) for loops
    * you can align the code, it allows it to be modified and read more easily
      * e.g.
        * ```
          int  bob0(int  val);
          char bob1(char val);
          ```
  * code should use zero-cost abstractions
    * for example use CRTP instead of virtual methods when possible
  * don't blindly follow OOP (or any other paradigms), use it where it is
    actually useful
