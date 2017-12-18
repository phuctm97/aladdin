/*
 * Created by phuctm97 on Sep 30th 2017
 */

#include "MyResourceInitializer.h"
#include "MyAppData.h"
#include "../prefabs/NodePrefab.h"
#include "../prefabs/SpritePrefab.h"
#include "../prefabs/MenuSelectPrefab.h"
#include "../prefabs/BitmapTextPrefab.h"
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
#include "../prefabs/AgrabahMarketGroundPrefab.h"
#include "../prefabs/AgrabahMarketStairsOnePrefab.h"
#include "../prefabs/AgrabahMarketStairsTwoPrefab.h"
#include "../prefabs/AgrabahMarketStairsThreePrefab.h"
#include "../prefabs/AgrabahMarketStairsFourPrefab.h"
#include "../prefabs/AgrabahMarketStairsFivePrefab.h"
#include "../prefabs/AgrabahMarketStairsSixPrefab.h"
#include "../prefabs/JafarQuarterGroundPrefab.h"

USING_NAMESPACE_ALA;

void MyResourceInitializer::doRun() {
  auto gameManager = GameManager::get();

  // Data
  new MyAppData( 1, 3, 1 );

  // Layers
  gameManager->addLayer( "Background" );
  gameManager->addLayer( "Second Background" );
  gameManager->addLayer( "Mass Character" );
  gameManager->addLayer( "Supporting Character" );
  gameManager->addLayer( "Main Character" );
  gameManager->addLayer( "Foreground" );
  gameManager->addLayer( "Second Foreground" );
  gameManager->addLayer( "UI" );
  gameManager->addLayer( "Debug" );

  // Scenes
  new SceneConfiguration( "jafar_quarter.scene", "scenes/jafar_quarter.scene" );

  // Textures
  new Sprite( "background.png", "textures/backgrounds/scene_1_0.png" );
  new Sprite( "foreground.png", "textures/backgrounds/scene_1_1.png" );
  new Sprite( "jafar_quarter_background.png", "textures/backgrounds/scene_2_1.png" );
  new Sprite( "aladdin.png", "textures/playable_characters/aladdin.png" );
  new Sprite( "enemy_explosions.png", "textures/miscellaneous/enemy_explosions.png" );
  new Sprite( "items.png", "textures/miscellaneous/items.png" );
  new Sprite( "cutscenes.png", "textures/miscellaneous/cutscenes.png" );
  new Sprite( "title.png", "textures/miscellaneous/title.png" );
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

  // Prefabs
  new SpritePrefab();
  new BitmapTextPrefab();

  new MenuSelectPrefab();

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

  new AgrabahMarketGroundPrefab();
  new AgrabahMarketStairsOnePrefab();
  new AgrabahMarketStairsTwoPrefab();
  new AgrabahMarketStairsThreePrefab();
  new AgrabahMarketStairsFourPrefab();
  new AgrabahMarketStairsFivePrefab();
  new AgrabahMarketStairsSixPrefab();

  new JafarQuarterGroundPrefab();

  // Dev tools
  new NodePrefab();
}
