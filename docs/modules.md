# Notes on C++20 Modules

Modules work in general with GCC 15 and CMake 4.2.0. There are however certain limitations and issues.

## Qt

### Qt in Exports

Qt headers are impossible to include within module interface units due to GCC compilation errors.
Module as simple as the following example will not compile:

```c++
module;

#include <QString>

export module example;

export int length(const QString &str) {
    return str.length();
}
```

There will be lots of compiler errors like

```
/usr/include/qt6/QtCore/qlatin1stringview.h:156:25: error: ‘short int QLatin1String::toShort(bool*, int) const’ exposes TU-local entity ‘T QtPrivate::toIntegral(ByteArrayView, bool*, int) [with T = short int; ByteArrayView = QByteArrayView; <template-parameter-1-3> = void]’
  156 |     [[nodiscard]] short toShort(bool *ok = nullptr, int base = 10) const
      |                         ^~~~~~~
      
In file included from /usr/include/qt6/QtCore/qbytearray.h:16:
/usr/include/qt6/QtCore/qbytearrayview.h:159:15: error: ‘constexpr QByteArrayView::QByteArrayView(const Pointer&) [with Pointer = const char*; typename std::enable_if<QtPrivate::IsCompatibleByteArrayPointer<Pointer>::value, bool>::type <anonymous> = true]’ exposes TU-local entity ‘constexpr qsizetype QtPrivate::lengthHelperPointer(const Char*) [with Char = char; qsizetype = long long int]’
  159 |     constexpr QByteArrayView(const Pointer &data) noexcept
      |               ^~~~~~~~~~~~~~
```

Which means modules cannot export anything that refers to Qt definitions.

The only solution I found so far is to gather all Qt related classes in a single implementation partition and
import all other modules from there. This is ugly and does not scale well.

### Qt MOC

Qt MOC cannot be built because custom Qt toolchain knows nothing about modules, dependency graph, etc.
The only solution I found was to ```set(CMAKE_AUTOMOC OFF)``` for the project and remove all Q_OBJECT macros from project
classes. This works if these classes don't use Qt syntax extensions like signals and slots. Translation
macros will not work either.

## Header Imports

Header imports are not supported by CMake currently at all.

## Import std

It works with significant limitations. There must be no STL headers included via ```#include``` either directly or
indirectly. Which means ```import std``` is practically impossible in module interface units. It can be used in module
implementation units for rather simple modules.
