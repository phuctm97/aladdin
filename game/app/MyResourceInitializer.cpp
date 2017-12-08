/*
 * Created by phuctm97 on Sep 30th 2017
 */

#include "MyResourceInitializer.h"
#include "../prefabs/NormalTextPrefab.h"
#include "../prefabs/BigTextPrefab.h"
#include "../prefabs/AladdinPrefab.h"
#include "../prefabs/ThrowableApplePrefab.h"
#include "../prefabs/ThinGuardPrefab.h"
#include "../prefabs/FatGuardPrefab.h"
#include "../prefabs/GroundPrefab.h"
#include "../prefabs/RopePrefab.h"
#include "../prefabs/StairPrefab.h"
#include "../prefabs/NodePrefab.h"
#include "../prefabs/FirePrefab.h"
#include "../prefabs/CharcoalBurnerPrefab.h"
#include "../prefabs//HandEnemyPrefab.h"
#include "../prefabs//ThrowVasePrefab.h"
#include "../prefabs//SalivaPrefab.h"
#include "../prefabs//CamelPrefab.h"

USING_NAMESPACE_ALA;

void MyResourceInitializer::doRun() {
  auto gameManager = GameManager::get();

  // Layers
  gameManager->addLayer( "Background" );
  gameManager->addLayer( "Character" );
  gameManager->addLayer( "Foreground" );

  // Textures
  new Sprite( "background.png", "textures/backgrounds/scene_1_0.png" );
  new Sprite( "foreground.png", "textures/backgrounds/scene_1_1.png" );
  new Sprite( "aladdin.png", "textures/playable_characters/aladdin.png" );
  new Sprite( "cutscenes.png", "textures/miscellaneous/cutscenes.png" );
  new Sprite( "guards.png", "textures/enemies/guards.png" );
  new Sprite( "civilian-enemies.png", "textures/enemies/civilian-enemies.png" );
  new Sprite( "jafar.png", "textures/bosses/jafar.png" );
  new Sprite("camel.png", "textures/non_playable_characters/camel.png");
  new Sprite("saliva.png", "textures/non_playable_characters/saliva.png");

  // Fonts
  new Font( "aladdin.ttf", "aladdin.ttf", "fonts" );
  new Font( "arcade.ttf", "arcade.ttf", "fonts" );

  // Animations
  new Animation( "aladdin.anm", "animations/playable_characters/aladdin.anm" );
  new Animation( "cutscenes.anm", "animations/miscellaneous/cutscenes.anm" );
  new Animation( "guards.anm", "animations/enemies/guards.anm" );
  new Animation( "jafar.anm", "animations/bosses/jafar.anm" );
  new Animation( "civilian-enemies.anm", "animations/enemies/civilian-enemies.anm" );
  new Animation("camel.anm", "animations/non_playable_characters/camel.anm");
  new Animation("saliva.anm", "animations/non_playable_characters/saliva.anm");

  // Prefabs
  new NormalTextPrefab();
  new BigTextPrefab();

  new AladdinPrefab();
  new ThrowableApplePrefab();
  new ThrowVasePrefab();

  new SalivaPrefab();
  new CamelPrefab();

  new ThinGuardPrefab();
  new FatGuardPrefab();
  new HandEnemyPrefab();

  new GroundPrefab();
  new RopePrefab();
  new StairPrefab();
  new FirePrefab();
  new CharcoalBurnerPrefab();

  // Dev tools
  new NodePrefab();
}
