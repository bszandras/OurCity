package Graphics;
import java.util.ArrayList;

import Graphics.Singletons.*;

import java.awt.Image;

public class Animation {
    private ArrayList<Image> animationFrames = new ArrayList<Image>();
    private int currentFrame = 0;
    public Animation(String path, int frames)
    {
        for(int i = 0; i < frames; i++)
        {
            String p = path + i + ".png";
            Image img = TextureDictionary.GetTexture(p);
            animationFrames.add(img);
        }
    }
    public Image GetNextFrame()
    {
        int returnable = currentFrame;
        currentFrame++;
        if(currentFrame >= animationFrames.size())
        {
            currentFrame = 0;
        }
        return animationFrames.get(returnable);
    }
}
