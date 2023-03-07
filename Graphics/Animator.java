package Graphics;
import javax.swing.Timer;
import java.awt.event.*;

public class Animator {
    private Sprite target;
    private Animation animation;
    private Timer tickTimer;
    private Boolean isPlaying = false;
    public Animator(Animation anim, int fps, Sprite target)
    {
        this.animation = anim;
        this.target = target;
        tickTimer = new Timer(1000 / fps, new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent ae) {
                PushAnimationFrame();
            }
        });
    }
    public void Play()
    {
        isPlaying = true;
        tickTimer.start();
    }
    public void Stop()
    {
        isPlaying = false;
        tickTimer.stop();
    }
    
    private void PushAnimationFrame()
    {
        if(!isPlaying)
        {
            return;
        }
        target.SetImage(animation.GetNextFrame());
    }
}
