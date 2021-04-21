#include "ball.h"
#include "collection_balls.h"

namespace poolgame {
    CollectionBalls::CollectionBalls() {
        std::cout<<positions_.size() << std::endl;

        for (size_t i = 0; i < 8; i++) {
            Ball ball = Ball(i + 1, false, colors_.at(i), positions_.at(i), 10);
            balls_.push_back(ball);
        }
        for (size_t i = 8; i < positions_.size(); i++) {
            Ball ball = Ball(i, true, colors_.at(i - 8), positions_.at(i), 10);
            balls_.push_back(ball);
        }
    }

    std::vector<Ball> CollectionBalls::GetBalls() {
        return balls_;
    }

    std::vector<glm::vec3> CollectionBalls::GetColors() {
        return colors_;
    }
    std::vector<glm::vec2> CollectionBalls::GetPositions() {
        return positions_;
    }
}

