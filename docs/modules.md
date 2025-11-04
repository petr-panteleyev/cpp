# Заметки по опыту использования модулей C++20

Модули, в целом, работают с GCC 15 и CMake 4.2.0 (начиная с 3.28). Однако, существует значительное количество проблем и ограничений.

## Qt

### Qt в экспорте

Заголовочные файлы Qt невозможно включать в блок интерфейса<sup>1</sup> модулей из-за ошибок компиляции GCC.
Даже простейший модуль, как в примере ниже, не скомпилируется:

```c++
module;

#include <QString>

export module example;

export int length(const QString &str) {
    return str.length();
}
```

Будет получено большое количество ошибок компиляции вида

```
/usr/include/qt6/QtCore/qlatin1stringview.h:156:25: error: ‘short int QLatin1String::toShort(bool*, int) const’ exposes TU-local entity ‘T QtPrivate::toIntegral(ByteArrayView, bool*, int) [with T = short int; ByteArrayView = QByteArrayView; <template-parameter-1-3> = void]’
  156 |     [[nodiscard]] short toShort(bool *ok = nullptr, int base = 10) const
      |                         ^~~~~~~
      
In file included from /usr/include/qt6/QtCore/qbytearray.h:16:
/usr/include/qt6/QtCore/qbytearrayview.h:159:15: error: ‘constexpr QByteArrayView::QByteArrayView(const Pointer&) [with Pointer = const char*; typename std::enable_if<QtPrivate::IsCompatibleByteArrayPointer<Pointer>::value, bool>::type <anonymous> = true]’ exposes TU-local entity ‘constexpr qsizetype QtPrivate::lengthHelperPointer(const Char*) [with Char = char; qsizetype = long long int]’
  159 |     constexpr QByteArrayView(const Pointer &data) noexcept
      |               ^~~~~~~~~~~~~~
```

Это означает, что, по сути, модули не могут экспортировать ничего что бы ссылалось на определения из Qt.

Единственное решение, которое мне пока удалось найти, заключается в перенесении всех классов, использующих Qt, в один
cpp-файл. Это позволяет избежать включения заголовков Qt в блоки интерфейса. Решение, конечно, уродливое и совершенно
не масштабируемое.

### Qt MOC

Qt MOC невозможно построить, поскольку соответствующие утилиты Qt ничего не знают о графе зависимостей между модулями
и пытаются построить свои файлы до сборки модулей.

Чтобы решить эту проблему, можно отключить опцию ```CMAKE_AUTOMOC``` и убрать макрос ```Q_OBJECT``` из соответствующих
классов проекта. Это можно делать только если эти классы не исользуют расширешия синтаксиса ```slots``` и ```signals```.
Видимо, макросы трансляции тоже не будут работать.

## Header Imports

Header imports в настоящее время не поддерживаются CMake даже в экспериментальном формате.

## Import std

Эта часть стандарта C++23 работает при включении экспериментальной функциональности CMake, но в реальности использовать ее не получается
из-за конфликтов между импортом и заголовками STL, транзитивно включаемыми из других заголовков.

Таким образом, практически невозможно использовать ```import std``` в блоках интерфейса. Можно использовать в блоках реализации<sup>2</sup> для
очень простых модулей, которые не зависят ни от чего кроме STL.

---

1 - module interface unit

2 - module implementation unit
