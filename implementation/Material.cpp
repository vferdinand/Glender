#include "../hpp/Material.hpp"

Material::Material() {
    name = "";
    ambient = {0.0, 0.0, 0.0, 1.0};
    difuse = {0.0, 0.0, 0.0, 1.0};
    specular = {0.0, 0.0, 0.0, 1.0};
    shininess = 0.0f;
    disolve = 1.0f;
    illum = 2; // Default illumination model
    reflectionFactor = 0.0;
}
Material::Material(std::string name, RGBA ambient, RGBA difuse, RGBA specular, float shininess, float disolve, int8_t illum, float reflectionsFactor) {
    this->name = name;
    this->ambient = ambient;
    this->difuse = difuse;
    this->specular = specular;
    this->shininess = shininess;
    this->disolve = disolve;
    this->illum = illum;
    this->reflectionFactor = reflectionsFactor;
}
const std::string Material::getName() const{
    return name;
}
const RGBA Material::getAmbient() const{
    return ambient;
}
const RGBA Material::getDifuse() const{
    return difuse;
}
const RGBA Material::getSpecular() const{
    return specular;
}
float Material::getShininess() const {
    return shininess;
}
float Material::getDissolve() const {
    return disolve;
}
int8_t Material::getIllum() const {
    return illum;
}

void Material::setName(std::string name){
    this->name = name;
}
void Material::setAmbient(RGBA ambient){
    this->ambient = ambient;
}
void Material::setDifuse(RGBA difuse){
    this->difuse = difuse;
}
void Material::setSpecular(RGBA specular){
    this->specular = specular;
}
void Material::setShininess(float shininess){
    this->shininess = shininess;
}
void Material::setDissolve(float disolve){
    this->disolve = disolve;
}
void Material::setIllum(int8_t illum){
    this->illum = illum;
}
void Material::setReflectionFactor(float reflectionFactor) { 
    this->reflectionFactor = reflectionFactor; 
}
float Material::getReflectionFactor() const { 
    return reflectionFactor; 
}