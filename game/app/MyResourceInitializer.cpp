/*
 * Created by phuctm97 on Sep 30th 2017
 */

#include "MyResourceInitializer.h"
#include "MyAppData.h"
#include "../prefabs/NodePrefab.h"
#include "../prefabs/QuadRendererPrefab.h"
#include "../prefabs/FadeInEffectPrefab.h"
#include "../prefabs/SceneFadeOutTransitionPrefab.h"
#include "../prefabs/SpritePrefab.h"
#include "../prefabs/BitmapTextPrefab.h"
#include "../prefabs/MenuSelectPrefab.h"
#include "../prefabs/DeathSceneControllerPrefab.h"
#include "../prefabs/AladdinAndAbuPrefab.h"
#include "../prefabs/LevelCompleteSceneControllerPrefab.h"
#include "../prefabs/RetrySceneControllerPrefab.h"
#include "../prefabs/HubPrefab.h"
#include "../prefabs/PlayableAladdinPrefab.h"
#include "../prefabs/ThrowableApplePrefab.h"
#include "../prefabs/ThrowableKnifePrefab.h"
#include "../prefabs/EatableApplePrefab.h"
#include "../prefabs/EatableHeartPrefab.h"
#include "../prefabs/GenieLampPrefab.h"
#include "../prefabs/GenieBonusPrefab.h"
#include "../prefabs/SpendThesePrefab.h"
#include "../prefabs/AbuBonusPrefab.h"
#include "../prefabs/CheckpointPrefab.h"
#include "../prefabs/EnemyExplosionOnePrefab.h"
#include "../prefabs/SmallFireworkPrefab.h"
#include "../prefabs/BigExplosionPrefab.h"
#include "../prefabs/EnemyExplosionTwoPrefab.h"
#include "../prefabs/FlamePrefab.h"
#include "../prefabs/CharcoalBurnerPrefab.h"
#include "../prefabs/FloatingSalivaPrefab.h"
#include "../prefabs/CamelPrefab.h"
#include "../prefabs/PeddlerPrefab.h"
#include "../prefabs/FallingVasePrefab.h"
#include "../prefabs/HandEnemyPrefab.h"
#include "../prefabs/GuardOnePrefab.h"
#include "../prefabs/GuardTwoPrefab.h"
#include "../prefabs/GuardThreePrefab.h"
#include "../prefabs/GuardFourPrefab.h"
#include "../prefabs/GuardFivePrefab.h"
#include "../prefabs/WallPrefab.h"
#include "../prefabs/ClimbableRopePrefab.h"
#include "../prefabs/HoldableBarPrefab.h"
#include "../prefabs/JumpableSpringPrefab.h"
#include "../prefabs/PlatformPrefab.h"
#include "../prefabs/PendalPrefab.h"
#include "../prefabs/AgrabahMarketParallaxPrefab.h"
#include "../prefabs/AgrabahMarketGroundPrefab.h"
#include "../prefabs/AgrabahMarketStairsOnePrefab.h"
#include "../prefabs/AgrabahMarketStairsTwoPrefab.h"
#include "../prefabs/AgrabahMarketStairsThreePrefab.h"
#include "../prefabs/AgrabahMarketStairsFourPrefab.h"
#include "../prefabs/AgrabahMarketStairsFivePrefab.h"
#include "../prefabs/AgrabahMarketStairsSixPrefab.h"
#include "../prefabs/JafarPrefab.h"
#include "../prefabs/JafarFirePrefab.h"
#include "../prefabs/JafarStarPrefab.h"
#include "../prefabs/JafarStarExplosionPrefab.h"
#include "../prefabs/JafarPalaceGroundPrefab.h"

USING_NAMESPACE_ALA;

void MyResourceInitializer::doRun() {
  auto gameManager = GameManager::get();

  // Data
  new MyAppData( 2, 1, 3, 1, { "agrabah_market.scene", "jafar_palace.scene" } );

  // Layers
  gameManager->addLayer( "Background" );
  gameManager->addLayer( "Second Background" );
  gameManager->addLayer( "Mass Character" );
  gameManager->addLayer( "Supporting Character" );
  gameManager->addLayer( "Main Character" );
  gameManager->addLayer( "Foreground" );
  gameManager->addLayer( "Second Foreground" );
  gameManager->addLayer( "UI" );
  gameManager->addLayer( "Overlay" );
  gameManager->addLayer( "Debug" );

  // Scenes
  new SceneConfiguration( "test.scene", "scenes/test.scene" );
  new SceneConfiguration( "menu.scene", "scenes/menu.scene" );
  new SceneConfiguration( "level_complete.scene", "scenes/level_complete.scene" );
  new SceneConfiguration( "death.scene", "scenes/death.scene" );
  new SceneConfiguration( "retry.scene", "scenes/retry.scene" );
  new SceneConfiguration( "agrabah_market.scene", "scenes/agrabah_market.scene" );
  new SceneConfiguration( "jafar_palace.scene", "scenes/jafar_palace.scene" );

  //Audio
  new AudioClip("Jafar Snake.wav", "audio/Jafar Snake.wav");
  new AudioClip("High Sword.wav", "audio/High Sword.wav");
  new AudioClip("Object Throw.wav", "audio/Object Throw.wav");
  new AudioClip("Apple Collect.wav", "audio/Apple Collect.wav");
  new AudioClip("Aladdin Push.wav", "audio/Aladdin Push.wav");
  new AudioClip("Apple Splat.wav", "audio/Apple Splat.wav");
  new AudioClip("Aladdin Hurt.wav", "audio/Aladdin Hurt.wav");
  new AudioClip("Low Sword.wav", "audio/Low Sword.wav");
  new AudioClip("Guard Beckon.wav", "audio/Guard Beckon.wav");
  new AudioClip("Sword Ching.wav", "audio/Sword Ching.wav");
  new AudioClip("Cloud Poof.wav", "audio/Cloud Poof.wav");
  new AudioClip("Genie Fumes.wav", "audio/Genie Fumes.wav");
  new AudioClip("Guard Hit 1.wav", "audio/Guard Hit 1.wav");
  new AudioClip("Guard Hit 2.wav", "audio/Guard Hit 2.wav");
  new AudioClip("Guard's Pants.wav", "audio/Guard's Pants.wav");
  new AudioClip("Camel Spit.wav", "audio/Camel Spit.wav");
  new AudioClip("Continue Point.wav", "audio/Continue Point.wav");
  new AudioClip("Fire From Coal.wav", "audio/Fire From Coal.wav");
  new AudioClip("Tip Toe.wav", "audio/Tip Toe.wav");
  new AudioClip("Flagpole.wav", "audio/Flagpole.wav");
  
  
  // Textures
  new Sprite( "agrabah_market_background.png", "textures/backgrounds/scene_1_0.png" );
  new Sprite( "agrabah_market_foreground.png", "textures/backgrounds/scene_1_1.png" );
  new Sprite( "agrabah_market_parallax.png", "textures/backgrounds/scene_1_2.png" );
  new Sprite( "jafar_palace_background.png", "textures/backgrounds/scene_2_1.png" );
  new Sprite( "aladdin.png", "textures/playable_characters/aladdin.png" );
  new Sprite( "enemy_explosions.png", "textures/miscellaneous/enemy_explosions.png" );
  new Sprite( "items.png", "textures/miscellaneous/items.png" );
  new Sprite( "cutscenes.png", "textures/miscellaneous/cutscenes.png" );
  new Sprite( "title.png", "textures/miscellaneous/title.png" );
  new Sprite( "victory.png", "textures/miscellaneous/victory.png" );
  new Sprite( "retry.png", "textures/miscellaneous/retry.png" );
  new Sprite( "font_one.png", "textures/miscellaneous/font_one.png" );
  new Sprite( "font_two.png", "textures/miscellaneous/font_two.png" );
  new Sprite( "guards.png", "textures/enemies/guards.png" );
  new Sprite( "civilian_enemies.png", "textures/enemies/civilian_enemies.png" );
  new Sprite( "jafar.png", "textures/bosses/jafar.png" );
  new Sprite( "camel.png", "textures/nonplayable_characters/camel.png" );
  new Sprite( "peddler.png", "textures/nonplayable_characters/peddler.png" );
  new Sprite( "abu.png", "textures/nonplayable_characters/abu.png" );

  // Fonts
  new Font( "aladdin.ttf", "aladdin.ttf", "fonts" );
  new Font( "arcade.ttf", "arcade.ttf", "fonts" );
  new BitmapFont( "one.fnt", "fonts/one.fnt" );
  new BitmapFont( "two.fnt", "fonts/two.fnt" );

  // Animations
  new Animation( "agrabah_market_parallax.anm", "animations/backgrounds/scene_1_2.anm" );
  new Animation( "aladdin.anm", "animations/playable_characters/aladdin.anm" );
  new Animation( "enemy_explosions.anm", "animations/miscellaneous/enemy_explosions.anm" );
  new Animation( "apple.anm", "animations/miscellaneous/apple.anm" );
  new Animation( "items.anm", "animations/miscellaneous/items.anm" );
  new Animation( "cutscenes.anm", "animations/miscellaneous/cutscenes.anm" );
  new Animation( "guards.anm", "animations/enemies/guards.anm" );
  new Animation( "civilian_enemies.anm", "animations/enemies/civilian_enemies.anm" );
  new Animation( "jafar.anm", "animations/bosses/jafar.anm" );
  new Animation( "camel.anm", "animations/nonplayable_characters/camel.anm" );
  new Animation( "peddler.anm", "animations/nonplayable_characters/peddler.anm" );
  new Animation( "abu.anm", "animations/nonplayable_characters/abu.anm" );

  // Audio
  new AudioClip( "Menu Change.wav", "audio/Menu Change.wav" );
  new AudioClip( "A Whole New World.wav", "audio/A Whole New World.wav" );
  new AudioClip( "Background Agrabahmarket.wav", "audio/Background Agrabahmarket.wav" );
  new AudioClip( "NameLevel Agrabahmarket.wav", "audio/NameLevel Agrabahmarket.wav" );
  new AudioClip( "Level Complete.wav", "audio/Level Complete.wav" );
  new AudioClip( "Retry.wav", "audio/Retry.wav" );

  // Prefabs
  new SpritePrefab();
  new BitmapTextPrefab();
  new FadeInEffectPrefab();
  new SceneFadeOutTransitionPrefab();

  new MenuSelectPrefab();

  new DeathSceneControllerPrefab();

  new AladdinAndAbuPrefab();
  new LevelCompleteSceneControllerPrefab();
  new RetrySceneControllerPrefab();

  new HubPrefab();
  new PlayableAladdinPrefab();
  new ThrowableApplePrefab();
  new ThrowableKnifePrefab();
  new EatableApplePrefab();
  new EatableHeartPrefab();
  new GenieLampPrefab();
  new GenieBonusPrefab();
  new SpendThesePrefab();
  new AbuBonusPrefab();
  new CheckpointPrefab();
  new EnemyExplosionOnePrefab();
  new SmallFireworkPrefab();
  new BigExplosionPrefab();
  new EnemyExplosionTwoPrefab();
  new FlamePrefab();
  new CharcoalBurnerPrefab();
  new FloatingSalivaPrefab();
  new CamelPrefab();
  new PeddlerPrefab();
  new FallingVasePrefab();
  new HandEnemyPrefab();
  new GuardOnePrefab();
  new GuardTwoPrefab();
  new GuardThreePrefab();
  new GuardFourPrefab();
  new GuardFivePrefab();
  new WallPrefab();
  new ClimbableRopePrefab();
  new HoldableBarPrefab();
  new JumpableSpringPrefab();
  new PlatformPrefab();
  new PendalPrefab();

  new AgrabahMarketParallaxPrefab();
  new AgrabahMarketGroundPrefab();
  new AgrabahMarketStairsOnePrefab();
  new AgrabahMarketStairsTwoPrefab();
  new AgrabahMarketStairsThreePrefab();
  new AgrabahMarketStairsFourPrefab();
  new AgrabahMarketStairsFivePrefab();
  new AgrabahMarketStairsSixPrefab();

  new JafarPrefab();
  new JafarFirePrefab();
  new JafarStarPrefab();
  new JafarStarExplosionPrefab();
  new JafarPalaceGroundPrefab();

  // Dev tools
  new NodePrefab();
  new QuadRendererPrefab();
}
