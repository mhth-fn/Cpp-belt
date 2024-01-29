#include "Common.h"

using namespace std;

// Этот файл сдаётся на проверку
// Здесь напишите реализацию необходимых классов-потомков `IShape`
class Rectangle : public IShape{
public:
  Rectangle() = default;

  std::unique_ptr<IShape> Clone() const override{
    return make_unique<Rectangle>(*this);
  }

  void SetPosition(Point point) override{
    point_ = point;
  }
  Point GetPosition() const override{
    return point_;
  }

  void SetSize(Size size) override{
    size_ = size;
  }
  Size GetSize() const override{
    return size_;
  }

  void SetTexture(std::shared_ptr<ITexture> texture) override{
    texture_ = move(texture);
  }
  ITexture* GetTexture() const override{
    return texture_.get();
  }

  // Рисует фигуру на указанном изображении
  void Draw(Image& image) const override{
    size_t size_y = point_.y + size_.height,
           size_x = point_.x + size_.width;
    
    Image texture;
    Size texture_size;
    if (texture_.get() != nullptr){
      texture = texture_->GetImage();
      texture_size = texture_->GetSize();
    }
    for (int i = point_.y; i < image.size() && i < size_y; ++i){
      for (int j = point_.x; j < image[i].size() && j < size_x; ++j){
        size_t texture_x = j - point_.x,
               texture_y = i - point_.y;
        if (!texture.empty() && texture_y < texture_size.height && texture_x < texture_size.width){
          image[i][j] = texture[texture_y][texture_x];
        } else {
          image[i][j] = '.';
        }
      }
    }
  }
private:
  Point point_;
  Size size_;
  std::shared_ptr<ITexture> texture_;

};
class Ellipse : public IShape{
public:
  Ellipse() = default;

  std::unique_ptr<IShape> Clone() const override{
    auto clone = *this;
    return make_unique<Ellipse>(clone);
  }

  void SetPosition(Point point) override{
    point_ = point;
  }
  Point GetPosition() const override{
    return point_;
  }

  void SetSize(Size size) override{
    size_ = size;
  }
  Size GetSize() const override{
    return size_;
  }

  void SetTexture(std::shared_ptr<ITexture> texture) override{
    texture_ = move(texture);
  }
  ITexture* GetTexture() const override{
    return texture_.get();
  }

  // Рисует фигуру на указанном изображении
  void Draw(Image& image) const override{
    size_t size_y = point_.y + size_.height,
           size_x = point_.x + size_.width;
    
    Image texture;
    Size texture_size;
    if (texture_.get() != nullptr){
      texture = texture_->GetImage();
      texture_size = texture_->GetSize();
    }
    for (int i = point_.y; i < image.size() && i < size_y; ++i){
      for (int j = point_.x; j < image[i].size() && j < size_x; ++j){
        int texture_x = j - point_.x,
            texture_y = i - point_.y;
        if (IsPointInEllipse({texture_x, texture_y}, size_)){
          if (!texture.empty() && texture_y < texture_size.height && texture_x < texture_size.width){
            image[i][j] = texture[texture_y][texture_x];
          } else {
            image[i][j] = '.';
          }
        }
      }
    }
  }
private:
  Point point_;
  Size size_;
  std::shared_ptr<ITexture> texture_;

  bool IsPointInRectangle(Point p) const{
    return (p.x >= point_.x &&
        p.x < (point_.x + size_.width) &&
        p.y >= point_.y &&
        p.y < (point_.y + size_.height));
  }
};


// Напишите реализацию функции
unique_ptr<IShape> MakeShape(ShapeType shape_type) {
  if (shape_type == ShapeType::Rectangle){
    return make_unique<Rectangle>();
  } else if (shape_type == ShapeType::Ellipse){
    return make_unique<Ellipse>();
  }
  return nullptr;

}