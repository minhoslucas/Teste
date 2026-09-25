#include <stdio.h>
#include <vector>
#include <filesystem>
#include <iostream>
#include <string>

namespace fs = std::filesystem;

#pragma pack(push, 1) //garantir os 40 bytes
struct Metadata {
    double dt;
    double delrt;
    unsigned int ns;
    unsigned int fintil;
    double dx;
    double dy;
};

struct Xlmap {
    int32_t xl_value;
    uint64_t xl_index;
};
#pragma pack(pop)

struct IlData {
    int il_num;
    std::vector<Xlmap> map;
    std::vector<float> pos;
    std::vector<_Float16> samples;
};

int getIlAmnt(const char* path){
    int amnt;
    for (const auto& file : fs::directory_iterator(path)){
        if (file.is_directory()){
            amnt++;
        }
    }

    return amnt;
}

bool getMetaData(const char* path, Metadata& metadata) {
    FILE* fp = std::fopen(path, "rb");
    if (fp == nullptr) {
        std::cerr << "Nao foi possivel abrir o arquivo: " << path << std::endl;
        return false;
    }

    if (std::fread(&metadata, sizeof(metadata), 1, fp) != 1) {
        std::cerr << "Nao foi possivel ler o arquivo: " << path << std::endl;
        std::fclose(fp);
        return false;
    }

    std::fclose(fp);
    return true;
}

//Ler um arquivo binário genérico
template <typename T>
bool readFile(const std::string *path, std::vector<T> &buff){
    FILE *fp = fopen(path, "rb");
    if (fp == nullptr){
        return false;
    }

    std::fseek(fp, 0, SEEK_END);
    int fsize = std::ftell(fp);
    std::fseet(fp, 0, SEEK_SET);

    buff.resize(fsize / sizeof(T));
    if (fsize > 0){
        std::fread(buff.data(), sizeof(T), buff.size, fp);
    }

    std::fclose(fp);
    return true;
}

IlData readIl(const std::string path, int il_num){
    IlData data;
    data.il_num = il_num;
    if (!readFile(path + "/samples", data.samples)){

    }
}

bool readBlockOfIlXl(const char *path, std::vector<_Float16>& samples, int il_per_block, int il_min, int il_max){
    samples.clear();
    int curr_il = -1, curr_count = 0, il_amnt = getIlAmnt("solnascente-3d/data/prestack/by_il");
    if (il_amnt < il_max){
        std::cerr << "Inline Máximo Maior que a quantidade de Inlines do arquivo." << std::endl;
        return false;
    }
}

int main() {
    Metadata metadata{};
    FILE *fp;
    //metadados
    if (!getMetaData("solnascente-3d/data/prestack/metadata", metadata)) {
        return 1;
    }

    //conta quantos il tem
    int count = 0;
    for (const auto& folder : fs::directory_iterator("solnascente-3d/data/prestack/by_il")){
        if (folder.is_directory()){
            count++;
        }
    }

    std::cout << "Número de Inlines: " << count << std::endl;
    std::cout << "dt:     " << metadata.dt << std::endl;
    std::cout << "delrt:  " << metadata.delrt << std::endl;
    std::cout << "ns:     " << metadata.ns << std::endl;
    std::cout << "fintil: " << metadata.fintil << std::endl;
    std::cout << "dx:     " << metadata.dx << std::endl;
    std::cout << "dy:     " << metadata.dy << std::endl;

    return 0;
}

/*PENDÊNCIAS:
- ler um inline por vez (ver se isso é uma boa)
- considerar leitura em blocos de crossline
- começar implementação do CRS brute force mesmo
- descobrir como que eu exporto os resultados*/