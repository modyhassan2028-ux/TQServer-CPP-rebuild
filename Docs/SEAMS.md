# Seams — where Syndicate.dll calls out

Counted from the binary: **99** indirect slots carrying **7238** call sites, and **2340** direct call
targets carrying **13703** sites.

## Indirect slots

| slot | sites | known as |
|---|---:|---|
| `0x1418233c0` | 3728 | invalid_parameter_noinfo |
| `0x141823030` | 776 | assert handler |
| `0x141823290` | 555 | - - |
| `0x141823050` | 332 | - - |
| `0x141823038` | 219 | - - |
| `0x141823400` | 194 | - - |
| `0x1418232a8` | 169 | - - |
| `0x1418233c8` | 129 | - - |
| `0x141823270` | 113 | - - |
| `0x141823280` | 97 | - - |
| `0x141823288` | 96 | - - |
| `0x1418233e8` | 93 | - - |
| `0x1418233f8` | 82 | - - |
| `0x141823040` | 54 | - - |
| `0x141823268` | 53 | - - |
| `0x141823048` | 49 | - - |
| `0x141823060` | 45 | - - |
| `0x1418230a8` | 42 | - - |

## Direct targets

| target | sites |
|---|---:|
| `0x1417f2fdc` | 875 |
| `0x1417f3166` | 548 |
| `0x1417214b0` | 378 |
| `0x1417f3154` | 287 |
| `0x141724850` | 168 |
| `0x1417f30a0` | 158 |
| `0x1417cad00` | 145 |
| `0x1417e0da0` | 120 |
| `0x1417f30c0` | 112 |
| `0x14178c8e0` | 109 |
| `0x1417e8016` | 107 |
| `0x141726110` | 96 |
| `0x14177e290` | 96 |
| `0x141785ea0` | 93 |

## Reading

Two slots carry most of the image: `0x1418233c0` (3728 sites) is the `invalid_parameter_noinfo`
stub that every standard-container precondition funnels into, and `0x141823030` (776) is the custom
assert handler. Both are already seams in the rewrite, which is why the hand pass could reproduce
the container bodies without touching the CRT.

The destructor and allocator families are not leaves: their bodies store an absolute vtable address
and then call through a slot. Generating them needs the slot named as a seam and the vtable symbols
resolved, so this inventory comes first.
