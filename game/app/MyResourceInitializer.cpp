/*
 * Created by phuctm97 on Sep 30th 2017
 */

#include "MyResourceInitializer.h"
#include "../prefabs/NormalTextPrefab.h"
#include "../prefabs/BigTextPrefab.h"
#include "../prefabs/HubPrefab.h"
#include "../prefabs/AladdinPrefab.h"
#include "../prefabs/ThrowableApplePrefab.h"
#include "../prefabs/ThinGuardPrefab.h"
#include "../prefabs/FatGuardPrefab.h"
#include "../prefabs/AdorableGuardPrefab.h"
#include "../prefabs/ThrowableKnifePrefab.h"
#include "../prefabs/AgrabahMarketGroundPrefab.h"
#include "../prefabs/RopePrefab.h"
#include "../prefabs/NodePrefab.h"
#include "../prefabs/FlamePrefab.h"
#include "../prefabs/CharcoalBurnerPrefab.h"
#include "../prefabs/StairOnePrefab.h"
#include "../prefabs/StaticMapBlockerPrefab.h"
#include "../prefabs/ApplePrefab.h"
#include "../prefabs/NodePrefab.h"
#include "../prefabs/EnemyExplosionPrefab.h"
#include "../prefabs/PlayableAladdinPrefab.h"

USING_NAMESPACE_ALA;

void MyResourceInitializer::doRun() {
  auto gameManager = GameManager::get();

  // Layers
  gameManager->addLayer( "Background" );
  gameManager->addLayer( "Sub Background" );
  gameManager->addLayer( "Character" );
  gameManager->addLayer( "Sub Character" );
  gameManager->addLayer( "Foreground" );
  gameManager->addLayer( "UI" );

  // Textures
  new Sprite( "background.png", "textures/backgrounds/scene_1_0.png" );
  new Sprite( "foreground.png", "textures/backgrounds/scene_1_1.png" );
  new Sprite( "aladdin.png", "textures/playable_characters/aladdin.png" );
  new Sprite( "cutscenes.png", "textures/miscellaneous/cutscenes.png" );
  new Sprite( "enemy_explosions.png", "textures/miscellaneous/enemy_explosions.png" );
  new Sprite( "title.png", "textures/miscellaneous/title.png" );
  new Sprite( "font_one.png", "textures/miscellaneous/font_one.png" );
  new Sprite( "font_two.png", "textures/miscellaneous/font_two.png" );
  new Sprite( "menu_select.png", "textures/miscellaneous/menu_select.png" );
  new Sprite( "items.png", "textures/miscellaneous/items.png" );
  new Sprite( "numbers.png", "textures/miscellaneous/numbers.png" );
  new Sprite( "guards.png", "textures/enemies/guards.png" );
  new Sprite( "civilian-enemies.png", "textures/enemies/civilian-enemies.png" );
  new Sprite( "jafar.png", "textures/bosses/jafar.png" );

  // Fonts
  new Font( "aladdin.ttf", "aladdin.ttf", "fonts" );
  new Font( "arcade.ttf", "arcade.ttf", "fonts" );
  new BitmapFont( "one.fnt", "fonts/one.fnt" );
  new BitmapFont( "two.fnt", "fonts/two.fnt" );

  // Animations
  new Animation( "aladdin.anm", "animations/playable_characters/aladdin.anm" );
  new Animation( "cutscenes.anm", "animations/miscellaneous/cutscenes.anm" );
  new Animation( "enemy_explosions.anm", "animations/miscellaneous/enemy_explosions.anm" );
  new Animation( "items.anm", "animations/miscellaneous/items.anm" );
  new Animation( "numbers.anm", "animations/miscellaneous/numbers.anm" );
  new Animation( "guards.anm", "animations/enemies/guards.anm" );
  new Animation( "jafar.anm", "animations/bosses/jafar.anm" );
  new Animation( "civilian-enemies.anm", "animations/enemies/civilian-enemies.anm" );
  new Animation( "apple.anm", "animations/miscellaneous/apple.anm" );

  // Prefabs
  new NormalTextPrefab();
  new BigTextPrefab();
  new HubPrefab();


  new PlayableAladdinPrefab();
  new AladdinPrefab();
  new ThrowableApplePrefab();
  new EnemyExplosionPrefab();


  new ThinGuardPrefab();
  new FatGuardPrefab();
  new AdorableGuardPrefab();
  new ThrowableKnifePrefab();

  new AgrabahMarketGroundPrefab();
  new RopePrefab();
  new FlamePrefab();
  new CharcoalBurnerPrefab();
  new StairOnePrefab();
  new StaticMapBlockerPrefab();
  new ApplePrefab();

  // Dev tools
  new NodePrefab();
}
