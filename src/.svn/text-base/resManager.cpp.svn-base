#include "resManager.h"
#include "log.h"

#include <boost/lexical_cast.hpp>
#include <boost/bind.hpp>

#include <algorithm>

boost::shared_ptr<ResourceManager> ResourceManager::pointerInstance;

boost::shared_ptr<ResourceManager> ResourceManager::instance(){
    if(pointerInstance == 0)
        pointerInstance.reset(new ResourceManager);

    return pointerInstance;
}

void ResourceManager::delInstance(){
    if(pointerInstance != 0)
        pointerInstance.reset();
}

void ResourceManager::init(Gosu::Graphics & g_){
    g = &g_;
}

boost::shared_ptr<Gosu::Image> ResourceManager::getImage(wstring path){
    imgMapIterator it = loadedImages.find(path);

    if(it == loadedImages.end())
        loadedImages[path].reset(new Gosu::Image(*g, path));    
        
    collectGarbage(path);
    return loadedImages[path];
}

boost::shared_ptr<Gosu::Font> ResourceManager::getFont(wstring path, int size){
    wstring key = path + boost::lexical_cast<wstring>(size);

    if(loadedFonts.find(key) == loadedFonts.end())
        loadedFonts[key].reset(new Gosu::Font(*g, path, size, 0));

    collectGarbage(key);
    return loadedFonts[key];
}

ResourceManager::ResourceManager(){ 
    lDEBUG << Log::CON("ResourceManager");
}

ResourceManager::~ResourceManager(){ 
    lDEBUG << Log::DES("ResourceManager");
}

void ResourceManager::collectGarbage(wstring bypass){
    for(imgMapIterator it = loadedImages.begin(); it != loadedImages.end(); ){
        if(it -> second.unique() && it -> first != bypass){
            loadedImages.erase(it++);
        }else{
            ++it;
        }
    }

    for(fontMapIterator it = loadedFonts.begin(); it != loadedFonts.end(); ){
        if(it -> second.unique() && it -> first != bypass){
            loadedFonts.erase(it++);
        }else{
            ++it;
        }
    }
    
}
