#include <collection_balls.h>
#include "pool_table.h"

namespace poolgame {

    PoolTable::PoolTable() {
        collection_of_balls_ = CollectionBalls();

    }

    void PoolTable::Display() const {
        DrawTable();
        DrawHoles();
        DrawBalls();
    }

    void PoolTable::AdvanceOneFrame() {

    }

    void PoolTable::DrawTable() const {
        glm::vec2 point_1 = glm::vec2(100, 250);
        glm::vec2 point_2 = glm::vec2(900, 750);
        cinder::gl::color(0, 0.38f, 0.11f);
        cinder::gl::drawSolidRect(cinder::Rectf(point_1.x, point_1.y, point_2.x, point_2.y));
        cinder::gl::color(0.36f, 0.20f, 0.09f);
        cinder::gl::drawStrokedRect(cinder::Rectf(point_1.x, point_1.y, point_2.x, point_2.y), 50);
    }

    void PoolTable::DrawHoles() const {
        glm::vec2 hole_1 = glm::vec2(120, 270);
        cinder::gl::color(0,0,0);
        cinder::gl::drawSolidCircle(hole_1, 25, -1);

        glm::vec2 hole_2 = glm::vec2(880, 730);
        cinder::gl::color(0,0,0);
        cinder::gl::drawSolidCircle(hole_2, 25, -1);

        glm::vec2 hole_3 = glm::vec2(120, 730);
        cinder::gl::color(0,0,0);
        cinder::gl::drawSolidCircle(hole_3, 25, -1);

        glm::vec2 hole_4 = glm::vec2(880, 270);
        cinder::gl::color(0,0,0);
        cinder::gl::drawSolidCircle(hole_4, 25, -1);

        glm::vec2 hole_5 = glm::vec2(500, 730);
        cinder::gl::color(0,0,0);
        cinder::gl::drawSolidCircle(hole_5, 25, -1);

        glm::vec2 hole_6 = glm::vec2(500, 270);
        cinder::gl::color(0,0,0);
        cinder::gl::drawSolidCircle(hole_6, 25, -1);
    }

    void PoolTable::DrawBalls() const {
        CollectionBalls collection_of_balls = CollectionBalls();
        for (size_t i = 0; i < collection_of_balls.GetBalls().size(); i++) {
            Ball ball = collection_of_balls.GetBalls().at(i);
            cinder::gl::color(ball.GetBallColor().x,ball.GetBallColor().y,ball.GetBallColor().z);
            cinder::gl::drawSolidCircle(ball.GetBallPosition(), ball.GetRadius(), -1);
        }
    }


}  // namespace idealgas
