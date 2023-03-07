package Graphics.Singletons;
import java.util.HashMap;
import java.awt.Image;
import javax.swing.ImageIcon;
import java.nio.file.*;

public class TextureDictionary {
    private static TextureDictionary instance = null;
    private HashMap<String, Image> sprites = new HashMap<>();
    private HashMap<String, Image> scaledSprites = new HashMap<>();
    public TextureDictionary()
    {
        instance = this;
    }
    private static void AddTexture(String path)
    {
        if(instance == null)
        {
            System.out.println("TextureDictionary instance is null");
            return;
        }
        //instance.sprites.put(path, new ImageIcon(("../" + path)).getImage());
        instance.sprites.put(path, new ImageIcon(Paths.get("").toAbsolutePath().toString() + "/" + path).getImage());
    }
    public static Image GetTexture(String path)
    {
        if(instance == null)
        {
            System.out.println("TextureDictionary instance is null");
            return null;
        }

        Image out = instance.sprites.get(path);
        if(out == null)
        {
            AddTexture(path);
            out = instance.sprites.get(path);
        }
        //System.out.println(instance.sprites.size());
        return out;
    }
    public static Image GetScaledTexture(String path)
    {
        if(instance == null)
        {
            System.out.println("TextureDictionary instance is null");
            return null;
        }

        Image out = instance.scaledSprites.get(path);
        //System.out.println(instance.sprites.size());
        return out;
    }
    public static void ScaleTextures(float scale)
    {
        //System.out.println(scale);
        for(String key : instance.sprites.keySet())
        {
            Image img = instance.sprites.get(key);
            img = img.getScaledInstance((int)(img.getWidth(null) * scale), (int)(img.getHeight(null) * scale), Image.SCALE_FAST);
            img = new ImageIcon(img).getImage();
            instance.scaledSprites.put(key, img);
        }
    }
}
