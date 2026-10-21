#pragma once
#include <cstdint>
#include <string>
#include <vector>

// Conquer .DMap loader (real collision data).
// Format verified empirically against d_antre01.DMap (mapId 1003):
//   +0   uint32 mapId
//   +4   uint32 zero
//   +8   char[]  puzzle scene path ("map\puzzle\xxx.pul"), null-terminated
//   ...  zero padding, two 8-byte bookkeeping groups (pul offsets/timestamps)
//   +N   uint32 width, uint32 height      (found by scan; 0x10c on the sample)
//   grid 6-byte cells [uint16 access][uint32 extra], row-major
//        access==1 -> walkable; 0 -> void (outside playable terrain);
//        large values (5000/600/1152...) -> special cells, treated blocked
//   trailer ~42KB additional data after the grid (skipped)

class CDMap {
public:
    struct Header {
        uint32_t dwMapId{0};
        std::string strPulPath;
        uint32_t dwWidth{0};
        uint32_t dwHeight{0};
        uint32_t dwGridOffset{0};
    };

    // returns false if the file is missing/not a dmap
    bool Load(const std::string& path);

    bool IsLoaded() const { return m_bLoaded; }
    uint32_t GetMapId() const { return m_dwMapId; }
    uint32_t GetWidth() const { return m_dwWidth; }
    uint32_t GetHeight() const { return m_dwHeight; }
    const Header& GetHeader() const { return m_header; }

    // real collision query; false outside the grid
    bool IsWalkable(uint32_t x, uint32_t y) const;

    // reads just the map id from a candidate file (cheap index scan)
    static bool PeekMapId(const std::string& path, uint32_t& dwIdOut);

private:
    uint32_t m_dwMapId{0};
    uint32_t m_dwWidth{0};
    uint32_t m_dwHeight{0};
    std::vector<uint16_t> m_access; // one entry per cell
    bool m_bLoaded{false};
    Header m_header;
};
