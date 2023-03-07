package Graphics.Singletons;
import java.util.ArrayList;
import Graphics.*;

public class OrthoWorld {
    private static OrthoWorld instance = null;
    Vector2 worldDimensions;
    Vector2 origoOffset;
    
    public ArrayList<Sprite> sprites = new ArrayList<>();
    public OrthoWorld(Vector2 dim, Vector2 windowSize)
    {
        instance = this;
        origoOffset = new Vector2(windowSize.getX() / 2, windowSize.getY() / 2);
        this.worldDimensions = dim;
    }
    public static void AddSprite(Sprite s)
    {
        instance.sprites.add(s);
    }
    public static ArrayList<Sprite> GetSprites()
    {
        return instance.sprites;
    }
    public static Vector2 WorldPositonToScreen(Vector2 pos)
    {
        if(instance == null)
        {
            System.out.println("World instance is null");
            return new Vector2(0,0);
        }
        return new Vector2(pos.getX() + instance.origoOffset.getX(), pos.getY() + instance.origoOffset.getY());
    }
    public static Boolean Exists()
    {
        return instance != null;
    }
    public static Vector2 getOrigoOffset()
    {
        if(instance == null)
        {
            System.out.println("World instance is null");
            return new Vector2(0,0);
        }
        return instance.origoOffset;
    }
}
