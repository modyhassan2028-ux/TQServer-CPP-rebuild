# Flower.dll — recovered vtables (no RTTI)

| vtable | dtor | slots |
|---|---|---|
| `0x140d9bcb8` | `0x140d93290` | 9 |
| `0x140d9da28` | `0x140d97c80` | 5 |
| `0x140d9db08` | `0x140d97fc0` | 5 |
| `0x140d9dc60` | `0x140d98170` | 5 |

## Mapping to source (2026-10-30)
| vtable | class | original file |
|---|---|---|
| `0x140d9bcb8` | `flower::CModule` | `modules/flower/src/module.cpp` |
| `0x140d9db08` | `flower::CMsgFlower` | `modules/flower/src/msg/msgflower.cpp` |
| `0x140d9dc60` | `flower::CMsgLog` | `modules/flower/src/msg/msglog.cpp` |
| `0x140d9da28` | `flower::CMsgLog` (earlier ctor variant) | `modules/flower/src/msg/msglog.cpp` |

Recovered structurally: slot 0 writes the vtable address back to `[rcx]` and then
tests the delete bit, which is the same dtor shape the RTTI path reveals.
