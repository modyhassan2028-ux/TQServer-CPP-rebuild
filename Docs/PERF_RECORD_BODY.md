# The record body 0x140ba51c0, call by call

Every block below is one log call. rcx carries the object, rdx the format, then
r8 and r9, then the stack slots from 0x20 up. The format text is read out of the
shipped binary at the address the code loads it from.

## call at 0x140ba5297
format @ 0x140bcbf60: `*********************************PerformanceInfo [%s]*********************************`

```
0x140ba522d  cmpq   $0x0,0x8(%rcx)
0x140ba5232  je     0x140ba5c8e
0x140ba5238  xor    %r13d,%r13d
0x140ba523b  mov    %r13d,0x84(%rsp)
0x140ba5243  lea    0x84(%rsp),%rcx
0x140ba524b  call   *0x2015f(%rip)   # 0x140bc53b0
0x140ba5251  lea    0x84(%rsp),%rcx
0x140ba5259  call   *0x20149(%rip)   # 0x140bc53a8
0x140ba525f  test   %rax,%rax
0x140ba5262  je     0x140ba5c8e
0x140ba5268  mov    %rax,%r9
0x140ba526b  lea    0x26d46(%rip),%r8   # 0x140bcbfb8
0x140ba5272  mov    $0x64,%edx
0x140ba5277  lea    0x260(%rsp),%rcx
0x140ba527f  call   *0x201a3(%rip)   # 0x140bc5428
0x140ba5285  lea    0x260(%rsp),%r8
0x140ba528d  lea    0x26ccc(%rip),%rdx   # 0x140bcbf60
0x140ba5294  mov    %r12,%rcx
0x140ba5297  call 0x140ba04e0
```

## call at 0x140ba5348
format @ 0x140bcbf38: `PdhCollectQueryData fail. status: %ld`

```
0x140ba52f4  movl   $0x40,0xc0(%rsp)
0x140ba52ff  lea    0xc0(%rsp),%rcx
0x140ba5307  call   *%rax
0x140ba5309  mov    0xa0(%r12),%rax
0x140ba5311  test   %rax,%rax
0x140ba5314  je     0x140ba532d
0x140ba5316  xor    %r9d,%r9d
0x140ba5319  mov    $0x138,%r8d
0x140ba531f  lea    0x120(%rsp),%rdx
0x140ba5327  lea    0x2(%r9),%ecx
0x140ba532b  call   *%rax
0x140ba532d  mov    0x8(%r12),%rcx
0x140ba5332  call   0x140bb74c2
0x140ba5337  test   %eax,%eax
0x140ba5339  je     0x140ba5352
0x140ba533b  mov    %eax,%r8d
0x140ba533e  lea    0x26bf3(%rip),%rdx   # 0x140bcbf38
0x140ba5345  mov    %r12,%rcx
0x140ba5348  call 0x140ba04e0
```

## call at 0x140ba53e6
format @ 0x140bcbee0: `Handle Count:    %10ld     Thread Count:       %10ld     Process Count:           %6ld`

```
0x140ba539d  mov    0x40(%r12),%rcx
0x140ba53a2  call   0x140bb74bc
0x140ba53a7  mov    %r13d,%ebx
0x140ba53aa  test   %eax,%eax
0x140ba53ac  cmove  0x78(%rsp),%ebx
0x140ba53b1  lea    0x70(%rsp),%r9
0x140ba53b6  xor    %r8d,%r8d
0x140ba53b9  mov    $0x100,%edx
0x140ba53be  mov    0x38(%r12),%rcx
0x140ba53c3  call   0x140bb74bc
0x140ba53c8  mov    %r13d,%ecx
0x140ba53cb  test   %eax,%eax
0x140ba53cd  cmove  0x78(%rsp),%ecx
0x140ba53d2  mov    %ecx,0x20(%rsp)
0x140ba53d6  mov    %ebx,%r9d
0x140ba53d9  mov    %edi,%r8d
0x140ba53dc  lea    0x26afd(%rip),%rdx   # 0x140bcbee0
0x140ba53e3  mov    %r12,%rcx
0x140ba53e6  call 0x140ba04e0
```

## call at 0x140ba549b
format @ 0x140bcbe50: `Physical Total:  %10I64d K   Physical Available: %10I64d K   System Cache(Physical):%8I64d K   System Cache Peak(Physical):   %10I64d K`

```
0x140ba5447  cqto
0x140ba5449  and    $0x3ff,%edx
0x140ba544f  lea    (%rdx,%rax,1),%rcx
0x140ba5453  sar    $0xa,%rcx
0x140ba5457  mov    0xd0(%rsp),%rax
0x140ba545f  cqto
0x140ba5461  and    $0x3ff,%edx
0x140ba5467  lea    (%rdx,%rax,1),%r9
0x140ba546b  sar    $0xa,%r9
0x140ba546f  mov    0xc8(%rsp),%rax
0x140ba5477  cqto
0x140ba5479  and    $0x3ff,%edx
0x140ba547f  lea    (%rdx,%rax,1),%r8
0x140ba5483  sar    $0xa,%r8
0x140ba5487  mov    %r10,0x28(%rsp)
0x140ba548c  mov    %rcx,0x20(%rsp)
0x140ba5491  lea    0x269b8(%rip),%rdx   # 0x140bcbe50
0x140ba5498  mov    %r12,%rcx
0x140ba549b  call 0x140ba04e0
```

## call at 0x140ba551c
format @ 0x140bcbdf0: `Kernel Total:    %10I64d K   Kernel Paged:       %10I64d K   Kernel Nonpaged:     %10I64d K`

```
0x140ba54d2  sar    $0xa,%rbx
0x140ba54d6  lea    0x70(%rsp),%r9
0x140ba54db  xor    %r8d,%r8d
0x140ba54de  mov    $0x400,%edx
0x140ba54e3  mov    0x28(%r12),%rcx
0x140ba54e8  call   0x140bb74bc
0x140ba54ed  test   %eax,%eax
0x140ba54ef  jne    0x140ba5506
0x140ba54f1  mov    0x78(%rsp),%rax
0x140ba54f6  cqto
0x140ba54f8  and    $0x3ff,%edx
0x140ba54fe  lea    (%rdx,%rax,1),%rdi
0x140ba5502  sar    $0xa,%rdi
0x140ba5506  lea    (%rdi,%rbx,1),%r8
0x140ba550a  mov    %rdi,0x20(%rsp)
0x140ba550f  mov    %rbx,%r9
0x140ba5512  lea    0x268d7(%rip),%rdx   # 0x140bcbdf0
0x140ba5519  mov    %r12,%rcx
0x140ba551c  call 0x140ba04e0
```

## call at 0x140ba55a8
format @ 0x140bcbd90: `Commit Total:    %10I64d K   Commit Limit:       %10I64d K   Commit Peak:         %10ld K`

```
0x140ba555f  mov    $0x400,%edx
0x140ba5564  mov    0x18(%r12),%rcx
0x140ba5569  call   0x140bb74bc
0x140ba556e  test   %eax,%eax
0x140ba5570  jne    0x140ba5587
0x140ba5572  mov    0x78(%rsp),%rax
0x140ba5577  cqto
0x140ba5579  and    $0x3ff,%edx
0x140ba557f  lea    (%rdx,%rax,1),%rdi
0x140ba5583  sar    $0xa,%rdi
0x140ba5587  mov    0x158(%rsp),%ecx
0x140ba558e  shl    $0xc,%ecx
0x140ba5591  shr    $0xa,%ecx
0x140ba5594  mov    %ecx,0x20(%rsp)
0x140ba5598  mov    %rdi,%r9
0x140ba559b  mov    %rbx,%r8
0x140ba559e  lea    0x267eb(%rip),%rdx   # 0x140bcbd90
0x140ba55a5  mov    %r12,%rcx
0x140ba55a8  call 0x140ba04e0
```

## call at 0x140ba5624
format @ 0x140bcbd30: `Page Fault(s):   %10ld     Page Reads(s):      %10ld     Page Writes(s):      %10ld`

```
0x140ba55db  mov    0x60(%r12),%rcx
0x140ba55e0  call   0x140bb74bc
0x140ba55e5  mov    %r13d,%ebx
0x140ba55e8  test   %eax,%eax
0x140ba55ea  cmove  0x78(%rsp),%ebx
0x140ba55ef  lea    0x70(%rsp),%r9
0x140ba55f4  xor    %r8d,%r8d
0x140ba55f7  mov    $0x100,%edx
0x140ba55fc  mov    0x70(%r12),%rcx
0x140ba5601  call   0x140bb74bc
0x140ba5606  mov    %r13d,%ecx
0x140ba5609  test   %eax,%eax
0x140ba560b  cmove  0x78(%rsp),%ecx
0x140ba5610  mov    %ecx,0x20(%rsp)
0x140ba5614  mov    %ebx,%r9d
0x140ba5617  mov    %edi,%r8d
0x140ba561a  lea    0x2670f(%rip),%rdx   # 0x140bcbd30
0x140ba5621  mov    %r12,%rcx
0x140ba5624  call 0x140ba04e0
```

## call at 0x140ba56d1
format @ 0x140bcbcb0: `Context Switch(s):%9ld     IO Read Operations(s):%8ld     IO Write Operations(s):%8ld     IO Other Operations(s):    %10ld`

```
0x140ba5686  call   0x140bb74bc
0x140ba568b  mov    %r13d,%ebx
0x140ba568e  test   %eax,%eax
0x140ba5690  cmove  0x78(%rsp),%ebx
0x140ba5695  lea    0x70(%rsp),%r9
0x140ba569a  xor    %r8d,%r8d
0x140ba569d  mov    $0x100,%edx
0x140ba56a2  mov    0x98(%r12),%rcx
0x140ba56aa  call   0x140bb74bc
0x140ba56af  mov    %r13d,%ecx
0x140ba56b2  test   %eax,%eax
0x140ba56b4  cmove  0x78(%rsp),%ecx
0x140ba56b9  mov    %ecx,0x28(%rsp)
0x140ba56bd  mov    %ebx,0x20(%rsp)
0x140ba56c1  mov    %edi,%r9d
0x140ba56c4  mov    %esi,%r8d
0x140ba56c7  lea    0x265e2(%rip),%rdx   # 0x140bcbcb0
0x140ba56ce  mov    %r12,%rcx
0x140ba56d1  call 0x140ba04e0
```

## call at 0x140ba56e0
format @ 0x140bcbca1: ``

```
0x140ba5690  cmove  0x78(%rsp),%ebx
0x140ba5695  lea    0x70(%rsp),%r9
0x140ba569a  xor    %r8d,%r8d
0x140ba569d  mov    $0x100,%edx
0x140ba56a2  mov    0x98(%r12),%rcx
0x140ba56aa  call   0x140bb74bc
0x140ba56af  mov    %r13d,%ecx
0x140ba56b2  test   %eax,%eax
0x140ba56b4  cmove  0x78(%rsp),%ecx
0x140ba56b9  mov    %ecx,0x28(%rsp)
0x140ba56bd  mov    %ebx,0x20(%rsp)
0x140ba56c1  mov    %edi,%r9d
0x140ba56c4  mov    %esi,%r8d
0x140ba56c7  lea    0x265e2(%rip),%rdx   # 0x140bcbcb0
0x140ba56ce  mov    %r12,%rcx
0x140ba56d1  call   0x140ba04e0
0x140ba56d6  lea    0x265c4(%rip),%rdx   # 0x140bcbca1
0x140ba56dd  mov    %r12,%rcx
0x140ba56e0  call 0x140ba04e0
```

## call at 0x140ba5775
format @ 0x140bcbbe0: `%8s %25s %7s %12s %12s %13s %11s %11s %13s %10s %10s %10s`

```
0x140ba5709  lea    0x26560(%rip),%rax   # 0x140bcbc70
0x140ba5710  mov    %rax,0x50(%rsp)
0x140ba5715  lea    0x26544(%rip),%rax   # 0x140bcbc60
0x140ba571c  mov    %rax,0x48(%rsp)
0x140ba5721  lea    0x26528(%rip),%rax   # 0x140bcbc50
0x140ba5728  mov    %rax,0x40(%rsp)
0x140ba572d  lea    0x2650c(%rip),%rax   # 0x140bcbc40
0x140ba5734  mov    %rax,0x38(%rsp)
0x140ba5739  lea    0x264f0(%rip),%rax   # 0x140bcbc30
0x140ba5740  mov    %rax,0x30(%rsp)
0x140ba5745  lea    0x264d8(%rip),%rax   # 0x140bcbc24
0x140ba574c  mov    %rax,0x28(%rsp)
0x140ba5751  lea    0x264c8(%rip),%rax   # 0x140bcbc20
0x140ba5758  mov    %rax,0x20(%rsp)
0x140ba575d  lea    0x2620c(%rip),%r9   # 0x140bcb970
0x140ba5764  lea    0x264b1(%rip),%r8   # 0x140bcbc1c
0x140ba576b  lea    0x2646e(%rip),%rdx   # 0x140bcbbe0
0x140ba5772  mov    %r12,%rcx
0x140ba5775  call 0x140ba04e0
```

## call at 0x140ba5bde
format @ 0x140bcbb90: `%8d %25s %6.3f%% %10ld K %10ld K %11ld K %11ld %11ld %13ld %10ld %10ld %10ld`

```
0x140ba5b7d  mov    %esi,0x68(%rsp)
0x140ba5b81  mov    %r13d,0x60(%rsp)
0x140ba5b86  mov    %r14d,0x58(%rsp)
0x140ba5b8b  mov    %r15d,0x50(%rsp)
0x140ba5b90  mov    0x8c(%rsp),%eax
0x140ba5b97  mov    %eax,0x48(%rsp)
0x140ba5b9b  mov    0x88(%rsp),%eax
0x140ba5ba2  mov    %eax,0x40(%rsp)
0x140ba5ba6  mov    0x98(%rsp),%rax
0x140ba5bae  mov    %eax,0x38(%rsp)
0x140ba5bb2  mov    0x90(%rsp),%rax
0x140ba5bba  mov    %eax,0x30(%rsp)
0x140ba5bbe  mov    0xa0(%rsp),%rax
0x140ba5bc6  mov    %eax,0x28(%rsp)
0x140ba5bca  movsd  %xmm6,0x20(%rsp)
0x140ba5bd0  mov    0x18(%rbx),%r8d
0x140ba5bd4  lea    0x25fb5(%rip),%rdx   # 0x140bcbb90
0x140ba5bdb  mov    %r12,%rcx
0x140ba5bde  call 0x140ba04e0
```

## What the binary says about the batch already ported

The counter setup at 0x140ba0600 was ported from the decompiled listing. Checked against
the shipped binary, it holds exactly:

- the sixteen paths, in this order: `\Memory\Committed Bytes`, `\Memory\Commit Limit`,
  `\Memory\Pool Paged Bytes`, `\Memory\Pool Nonpaged Bytes`, `\Process(_Total)\Handle Count`,
  `\System\Processes`, `\System\Threads`, `\Memory\Cache Bytes`, `\Memory\Cache Bytes Peak`,
  `\Memory\Page Faults/sec`, `\Memory\Page Reads/sec`, `\Memory\Page Writes/sec`,
  `\System\Context Switches/sec`, `\Process(_Total)\IO Read Operations/sec`,
  `\Process(_Total)\IO Write Operations/sec`, `\Process(_Total)\IO Other Operations/sec`.
- the sixteen counter-out slots: 10, 18, 20, 28, 30, 38, 40, 48, 50, 58, 60, **70**, **80**,
  88, 90, 98. The two gaps at 68 and 78 are confirmed in the instructions, not just in the
  decompiled text.
- the failure line, read out of the image at 0x140bcb038: `PdhOpenQuery fail. status: %ld`.

## Notes for the port of the record body

- The second call's format is `PdhCollectQueryData fail. status: %ld` (at 0x140bcbf38), not
  an open failure: it sits right after the first collect, before the retry.
- The last call at 0x140ba5bde carries a double in the fifth slot (r8 is an int field of the
  node at +0x18, the stack slots carry ints, and `movsd %xmm6,0x20(%rsp)` puts a floating
  value where `%6.3f%%` expects it).
- The row format at 0x140bcbb90 is
  `%8d %25s %6.3f%% %10ld K %10ld K %11ld K %11ld %11ld %13ld %10ld %10ld %10ld`, and the
  header at 0x140bcbbe0 is `%8s %25s %7s %12s %12s %13s %11s %11s %13s %10s %10s %10s`.
