#include "Worm_segment.h"
#include <cmath>
#include <iostream>
#include <memory>

using namespace sf;

Worm_segment::Worm_segment(std::shared_ptr<Vector2f> const p1, 
                           std::shared_ptr<Vector2f> const p2)
: next{nullptr}, p1{p1}, p2{p2}, rotation{0} 
{
    p3 = std::make_shared<Vector2f>(Vector2f(p1->x, p1->y));
    p4 = std::make_shared<Vector2f>(Vector2f(p2->x, p2->y));
}

void Worm_segment::add_segments(int amount)
{
    if (amount > 0)
    {
        if (next != nullptr)
        {
            next -> add_segments(amount);
        }
        else
        {
            next = std::make_unique<Worm_segment>(Worm_segment(p3, p4));
            next -> add_segments(--amount);
        }
    }
}

void Worm_segment::remove_last_segment()
{
    if (next != nullptr)
    {
        if (next -> next == nullptr)
        {
            std::shared_ptr<Worm_segment> tmp;
            next.swap(tmp);
        }
        else
        {
            next -> remove_last_segment();
        }
    }
}

int Worm_segment::get_segment_count()
{
    int count{1};
    if (next != nullptr)
    {
        count = next -> get_segment_count();
        ++count;
    }

    return count;
}

void Worm_segment::update(double const r)
{
    if (next != nullptr)
    {
        next -> update(rotation);
    }
    
    *p3 = *p1;
    *p4 = *p2;
    rotation = r;
}

void Worm_segment::draw(RenderWindow& window)
{
    if (next != nullptr)
    {
        next -> draw(window);
    }
    
    segment.setPointCount(4);
    segment.setPoint(0, *p1);
    segment.setPoint(1, *p2);
    segment.setPoint(2, *p4);
    segment.setPoint(3, *p3);

    window.draw(segment);
}

FloatRect Worm_segment::get_bounds()
{
    return segment.getLocalBounds();
}

double Worm_segment::get_rotation()
{
    return rotation;
}