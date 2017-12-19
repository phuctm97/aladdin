#include "QuadRendererPrefab.h"

USING_NAMESPACE_ALA;

ALA_CLASS_SOURCE_1(QuadRendererPrefab, ala::PrefabV2)

void QuadRendererPrefab::doInstantiate( ala::GameObject* object, std::istringstream& argsStream ) const {
  // args
  const auto index = nextString( argsStream );

  // constants
  const auto gameManager = GameManager::get();

  const auto quadTree = gameManager->getRunningScene()->getQuadTree();

  // offset
  const int nodeLevel = index.size();
  const auto nodeWidth = quadTree->getUnitWidth() * powf( 2, 1.0f * quadTree->getLevel() - nodeLevel );
  const auto nodeHeight = quadTree->getUnitHeight() * powf( 2, 1.0f * quadTree->getLevel() - nodeLevel );
  auto nodeOffsetX = 0.0f;
  auto nodeOffsetY = 0.0f;

  auto w = nodeWidth;
  auto h = nodeHeight;
  for ( int i = 0; i < nodeLevel; i++, w /= 2, h /= 2 ) {
    const auto c = index[i];
    switch ( c ) {
    case '0': break;
    case '1':
      nodeOffsetX += nodeWidth;
      break;
    case '2':
      nodeOffsetY += nodeHeight;
      break;
    case '3':
      nodeOffsetX += nodeWidth;
      nodeOffsetY += nodeHeight;
      break;
    default: break;
    }
  }

  // components
  const auto rect = new RectRenderer( object, Vec2( nodeOffsetX + nodeWidth / 2 + quadTree->getSpaceMinX(),
                                                    nodeOffsetY + nodeHeight / 2 + quadTree->getSpaceMinY() ),
                                      Size( nodeWidth, nodeHeight ),
                                      Color( 0, 255, 255, 100 ) );
  rect->setZOrder( 10 );
}
