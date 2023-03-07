package Graphics;

import Graphics.Singletons.*;

public class Status {
    private Animator animator;
    private Sprite ownSprite;
    //referencia az entitásra aminek a státusza
    //a konstruktor majd a referencia alapján pozícionálja magát
    public Status(int x, int y, int sortingHeight) {
        ownSprite = new Sprite(x, y, "Graphics/AnimationTest/status-test-frame0.png");
        ownSprite.AddSortingWeightY(sortingHeight * 64);
        OrthoWorld.AddSprite(ownSprite);

        Animation anim = new Animation("Graphics/AnimationTest/status-test-frame", 3);
        this.animator = new Animator(anim, 6, ownSprite);
        this.animator.Play();
    }
}
