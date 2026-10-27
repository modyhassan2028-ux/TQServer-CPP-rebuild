# System tests

Standalone C++ tests for the gameplay systems (bank interest, riding,
warehouse round-trip, enchant ladder, lottery gate/clamp, daily quest
state machine). Build and run one, e.g.:

    zig c++ -std=c++17 -IExe/MsgServer -Iinclude -ICore/CQBase \
        -ICore/DB -ICore/Root -D'__declspec(x)=' -o /tmp/interesttest \
        msgserver/*.cpp Core/CQBase/SHA1.cpp Core/CQBase/Msg.cpp \
        Core/CQBase/StringPacker.cpp stubs interest_test.cpp

Each test asserts the exact payout/ladder/state math the live commands
use, so a regression fails loudly at build time.
