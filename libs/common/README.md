# Common

## ObservableValue

Template class based on the idea of JavaFX class with the same name.
Only simple value change subscription is implemented.

## EnumClass

Template class imitating Java enum.

## Decimal

Simplified decimal value based on Java BigDecimal. Current implementation is rather limited:
+ unscaled value should fit into unsigned long long;
+ only positive scale values are allowed;
+ precision is not used;
+ only 2 rounding modes are supported;
+ no checks for overflow/underflow;
+ test coverage is incomplete.

The primary goal of this implementation is to support monetary values stored in database as DECIMAL(p,s).
