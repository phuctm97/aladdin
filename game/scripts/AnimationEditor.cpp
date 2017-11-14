#include "AnimationEditor.h"

USING_NAMESPACE_ALA;

AnimationEditor::AnimationEditor( ala::GameObject* gameObject, const std::string& actionName, const std::string& name )
  : GameObjectComponent( gameObject, name ), _logger( "AnimationEditor" ), _actionName( actionName ) {}

bool AnimationEditor::onPreInitialize() {
  const auto animator = getGameObject()->getComponentT<Animator>();
  if (animator == NULL) return false;
  animator->setAction(_actionName);

  const auto spriteRenderer = getGameObject()->getComponentT<SpriteRenderer>();
  if ( spriteRenderer == NULL ) return false;

  const auto spriteRendererDuplicate = new SpriteRenderer( getGameObject(), spriteRenderer->getSprite(),
                                                           "AnimationEditor-SpriteRenderer" );
  spriteRendererDuplicate->setSourceRect( spriteRenderer->getSourceRect() );
  spriteRendererDuplicate->setOffset( spriteRenderer->getOffset() );
  spriteRendererDuplicate->setBackColor( spriteRenderer->getBackColor() );
  spriteRendererDuplicate->setZOrder( spriteRenderer->getZOrder() );
  spriteRenderer->setZOrder( spriteRenderer->getZOrder() + 1 );
  spriteRendererDuplicate->initialize();
  return true;
}

void AnimationEditor::onUpdate( const float delta ) {
  const auto animator = getGameObject()->getComponentT<Animator>();
  const auto spriteRenderer = getGameObject()->getComponentT<SpriteRenderer>();
  const auto spriteRendererDuplicate = static_cast<SpriteRenderer*>(getGameObject()
    ->getComponent( "AnimationEditor-SpriteRenderer" ));
  if ( animator == NULL || spriteRenderer == NULL || spriteRendererDuplicate == NULL ) return;

  const auto input = Input::get();
  if ( input->getKeyDown( ALA_KEY_SPACE ) ) {
    spriteRendererDuplicate->setSourceRect( spriteRenderer->getSourceRect() );
    spriteRendererDuplicate->setOffset( spriteRenderer->getOffset() );
    spriteRendererDuplicate->setBackColor( spriteRenderer->getBackColor() );
    spriteRendererDuplicate->setZOrder(spriteRenderer->getZOrder());
    spriteRenderer->setZOrder(spriteRenderer->getZOrder() + 1);
    animator->playNext();

    if ( animator->getCurrentFrameIndex() == 0 ) {
      _logger.info( "Animation started again" );
    }
  }

  else if ( input->getKeyDown( ALA_KEY_RETURN ) ) {
    std::stringstream ss;
    ss << "\n<Animation";
    ss << " name=\"" << animator->getActionName() << "\"";
    ss << " imagePath=\"" << animator->getAction()->getTextureName() << "\"";
    ss << " interval=\"" << animator->getAction()->getInterval() << "\"";
    ss << " isLoop=\"" << (animator->getAction()->isLoop() ? "true" : "false") << "\"";
    ss << ">";

    for ( const auto& frame : animator->getAction()->getFrames() ) {
      ss << "\n\t<sprite";
      ss << " x=\"" << frame.first.getMinX() << "\"";
      ss << " y=\"" << frame.first.getMinY() << "\"";
      ss << " w=\"" << frame.first.getSize().getWidth() << "\"";
      ss << " h=\"" << frame.first.getSize().getHeight() << "\"";
      ss << " offsetX=\"" << frame.second.getX() << "\"";
      ss << " offsetY=\"" << frame.second.getY() << "\"";
      ss << " />";
    }

    ss << "\n</Animation>\n";
    _logger.info( ss.str().c_str() );
  }

  auto offset = animator->getCurrentFrameOffset();

  if ( input->getKeyDown( ALA_KEY_LEFT_ARROW ) ) {
    offset.setX( offset.getX() - 0.5f );
  }
  else if ( input->getKeyDown( ALA_KEY_RIGHT_ARROW ) ) {
    offset.setX( offset.getX() + 0.5f);
  }
  else if ( input->getKeyDown( ALA_KEY_UP_ARROW ) ) {
    offset.setY( offset.getY() + 0.5f);
  }
  else if ( input->getKeyDown( ALA_KEY_DOWN_ARROW ) ) {
    offset.setY( offset.getY() - 0.5f);
  }

  spriteRenderer->setOffset( offset );
  animator->getAction()->getFrames()[animator->getCurrentFrameIndex()].second = offset;

  animator->pause();
}
