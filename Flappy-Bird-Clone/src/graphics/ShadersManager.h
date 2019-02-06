//
//  ShadersManager.hpp
//  Flappy-Bird-Clone
//
//  Created by Túlio Henrique on 05/02/19.
//  Copyright © 2019 Túlio Henrique. All rights reserved.
//

#ifndef ShadersManager_h
#define ShadersManager_h

#include "Shader.h"

#include <memory>

class ShadersManager {
private:
    ShadersManager() {}
    
    ShadersManager(ShadersManager const&);
    void operator=(ShadersManager const&);
    
public:
    inline static ShadersManager& getInstance() {
        static ShadersManager instance;
        return instance;
    }
    
    void init();
    
    inline Shader* getBackgroundShader() { return m_backgroundShader.get(); }
private:
    std::shared_ptr<Shader> m_backgroundShader;
};

#endif /* ShadersManager_h */
