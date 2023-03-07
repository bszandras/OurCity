package Graphics;
public class Vector2 {
    int x;
    int y;
    
    public Vector2()
    {
        x = 0;
        y = 0;
    }
    public Vector2(int x, int y)
    {
        this.x = x;
        this.y = y;
    }
    public int getX() {
        return x;
    }
    public int getY() {
        return y;
    }
    public void Add(Vector2 v)
    {
        this.x += v.getX();
        this.y += v.getY();
    }
    public void Sub(Vector2 v)
    {
        this.x -= v.getX();
        this.y -= v.getY();
    }
    public void Scale(float s)
    {
        this.x *= s;
        this.y *= s;
    }
    public void Div(float d)
    {
        this.x /= d;
        this.y /= d;
    }
    @Override
    public String toString() {
        return "Vector2 [x=" + x + ", y=" + y + "]";
    }

    //statics
    public static Vector2 Add(Vector2 v1, Vector2 v2)
    {
        return new Vector2(v1.getX() + v2.getX(), v1.getY() + v2.getY());
    }
    public static Vector2 Sub(Vector2 v1, Vector2 v2)
    {
        return new Vector2(v1.getX() - v2.getX(), v1.getY() - v2.getY());
    }
    public static Boolean Equals(Vector2 v1, Vector2 v2)
    {
        return v1.getX() == v2.getX() && v1.getY() == v2.getY();
    }
}
