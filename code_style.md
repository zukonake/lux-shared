# Lux - Code style

-syntax
  -types use `PascalCase`
  -identifiers use `snake_case`
  -constants use `SCREAMING_SNAKE_CASE`
  -identifiers (variable names etc.) should make sense
    -don't be afraid to shorten identifiers that are known from the context
      -e.g. `vertex` to `vert` in a rendering function
      -`i`, `j` and similar are allowed in (non-range-based) for loops
-code should use zero-cost abstractions
  -for example use CRTP instead of virtual methods when possible
-follow the DRY principle
