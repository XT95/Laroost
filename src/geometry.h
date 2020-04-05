#ifndef GEOMETRY_H
#define GEOMETRY_H

#define BUFFER_OFFSET(i) ((char *)NULL + (i))

class Geometry
{
public:
    Geometry();
    ~Geometry();

    virtual void draw();
};

#endif // GEOMETRY_H
