#include "../hpp/Material.hpp"

Material::Material(std::string name, RGBA ka, RGBA kd, RGBA ks){
    this->name = name;
    this->ka = ka;
    this->kd = kd;
    this->ks = ks;
}
const std::string Material::getName() const{
    return name;
}
const RGBA Material::getKa() const{
    return ka;
}
const RGBA Material::getKd() const{
    return kd;
}
const RGBA Material::getKs() const{
    return ks;
}

void Material::setName(std::string name){
    this->name = name;
}
void Material::setKa(RGBA ka){
    this->ka = ka;
}
void Material::setKd(RGBA kd){
    this->kd = kd;
}
void Material::setKs(RGBA ks){
    this->ks = ks;
}