#include "DMap.h"

#include <cstdio>
#include <cstring>
#include <fstream>
#include <algorithm>

bool CDMap::PeekMapId(const std::string& path, uint32_t& dwIdOut) {
    std::ifstream in(path, std::ios::binary);
    if (!in) return false;
    uint32_t id = 0;
    in.read(reinterpret_cast<char*>(&id), 4);
    if (!in || id < 500 || id > 100000) return false; // plausible map ids only
    dwIdOut = id;
    return true;
}

bool CDMap::Load(const std::string& path) {
    std::ifstream in(path, std::ios::binary);
    if (!in) return false;

    std::vector<uint8_t> buf((std::istreambuf_iterator<char>(in)),
                               std::istreambuf_iterator<char>());
    if (buf.size() < 512) return false;

    std::memcpy(&m_dwMapId, buf.data(), 4);
    if (m_dwMapId < 500 || m_dwMapId > 100000) return false;

    // puzzle scene path: null-terminated from +8
    size_t pulEnd = 8;
    while (pulEnd < 256 && buf[pulEnd] != 0) ++pulEnd;
    m_header.strPulPath.assign(reinterpret_cast<const char*>(buf.data() + 8), pulEnd - 8);

    // locate the width/height: scan for two u32s (w,h) where w*h*6 fits in
    // the remaining bytes with a small trailer (see header comment)
    const size_t n = buf.size();
    size_t start = (8 + m_header.strPulPath.size() + 4) & ~size_t(3);
    for (size_t off = start; off + 12 < n; off += 4) {
        uint32_t w, h;
        std::memcpy(&w, buf.data() + off, 4);
        std::memcpy(&h, buf.data() + off + 4, 4);
        if (w < 16 || w > 8192 || h < 16 || h > 8192) continue;
        unsigned long long cells = (unsigned long long)w * h;
        unsigned long long grid = cells * 6;
        unsigned long long avail = n - (off + 8);
        if (grid > avail) continue;
        if (avail - grid > cells) continue; // trailer must be smaller than the grid
        // sanity: at least 2% of cells must have access==1 (walkable)
        m_dwWidth = w;
        m_dwHeight = h;
        m_access.resize(cells);
        const uint8_t* pGrid = buf.data() + off + 8;
        size_t walkable = 0;
        for (unsigned long long i = 0; i < cells; ++i) {
            uint16_t acc;
            std::memcpy(&acc, pGrid + i * 6, 2);
            m_access[i] = acc;
            if (acc == 1) ++walkable;
        }
        if (walkable < cells / 50) continue; // false positive; keep scanning

        m_header.dwMapId = m_dwMapId;
        m_header.dwWidth = w;
        m_header.dwHeight = h;
        m_header.dwGridOffset = static_cast<uint32_t>(off);
        m_bLoaded = true;
        printf("[DMAP] %s: id=%u grid %ux%u @+0x%x (%zu walkable cells, %.1f%%)\n",
               path.c_str(), m_dwMapId, w, h, (unsigned)off,
               walkable, 100.0 * walkable / cells);
        return true;
    }
    printf("[DMAP] %s: could not locate collision grid\n", path.c_str());
    return false;
}

bool CDMap::IsWalkable(uint32_t x, uint32_t y) const {
    if (!m_bLoaded || x >= m_dwWidth || y >= m_dwHeight) return false;
    return m_access[(size_t)y * m_dwWidth + x] == 1;
}
