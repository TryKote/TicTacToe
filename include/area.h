#ifndef AREA_H
#define AREA_H

struct cell {
    bool empty = true;
    bool value; //X -- true, 0 -- false
};

class area
{
    public:
        area();
        ~area();
        void set(int x, int y, bool val);
        cell **getMap();

    protected:

    private:
        cell **floor = new cell *[3]; //[x][y]
};

#endif // AREA_H
