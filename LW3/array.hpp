#include "figure.hpp"

class Array {
   private:
    Figure** _figures;
    size_t _size;

   public:
    Array();
    Array(size_t size);
    virtual ~Array();

    auto operator[](size_t index) const -> Figure*;
    auto delete_figure(size_t index) -> void;
    auto common_surface() -> double;
};