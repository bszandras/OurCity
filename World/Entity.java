package World;
import Graphics.*;
import Graphics.Singletons.OrthoWorld;

public class Entity {
    private Sprite sprite;
    public Entity(int i, int j)
    {
        sprite = new Sprite((i * 64) - j * 32, (j * 64) - j * 40,  "Graphics/OrthoSprites/ortho-house3.png");
    
        OrthoWorld.AddSprite(sprite);
    }
}