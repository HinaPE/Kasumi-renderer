#ifndef KASUMI_TESTURE_H
#define KASUMI_TESTURE_H

#include <string>
#include <memory>

namespace Kasumi
{
class Texture
{
public:
    Texture(const std::string &path);
    Texture(const Texture &src) = delete;
    Texture(Texture &&src) noexcept = default;
    ~Texture() = default;
    void operator=(const Texture &src) = delete;
    auto operator=(Texture &&src) noexcept -> Texture & = default;

public:
    void bind(int texture_idx = 0) const;

private:
    unsigned int ID;
    int width, height, nr_channels;
};
using TexturePtr = std::shared_ptr<Texture>;
}

#endif //KASUMI_TESTURE_H
