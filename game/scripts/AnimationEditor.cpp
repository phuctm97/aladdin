#include "AnimationEditor.h"

USING_NAMESPACE_ALA;

AnimationEditor::AnimationEditor( ala::GameObject* gameObject, const std::string& entryAction,
                                  ala::Animation* animationName, const std::string& name )
  : GameObjectComponent( gameObject, name ) {}

AnimationEditor::AnimationEditor( ala::GameObject* gameObject, const std::string& entryAction,
                                  const std::string& animationResourceName, const std::string& name )
  : GameObjectComponent( gameObject, name ) {}
