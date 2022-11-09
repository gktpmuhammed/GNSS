#include <iostream>
#include "navigation_engine.hpp"

/// Bu fonksiyon verilen data typeların boyutu kadar dosyadan byte okuyor ve verilen buff variableı içerisine yazıyor.
template <typename T>
std::istream &read_file(std::ifstream &file, T &buff)
{
    return file.read(reinterpret_cast<char *>(&buff), sizeof(buff));
}
NavEng<SatelliteSystem::SBAS> navEng;

int main() {
    std::ifstream infile(navEng.input_file_path, std::ios_base::binary);
    if (!infile.is_open())
        exit(EXIT_FAILURE);

    sbasHelperFunctions::write_rinex_header(navEng.output_file_path);


    while (!infile.eof()) {
        uint8_t prem1,prem2,classId,msgId,gnssId,svId,CK_A,CK_B,reserved0,freqId,numWords,chn,version,reserved1;
        uint16_t length;
        uint32_t dwrd[10];

        read_file(infile, prem1);
        if (prem1 == 181) {

            read_file(infile, prem2);
            if (prem2 == 98) {

                read_file(infile, classId);
                if (classId == 2) {

                    read_file(infile, msgId);
                    if (msgId == 19) {

                        read_file(infile, length);
                        read_file(infile, gnssId);

                        if (gnssId == 1) {

                            read_file(infile, svId);
                            if (svId >= 120 && svId <= 158) {
                                /// Normalde payload 44 byte uzunluğunda ama gnssId ve svId öncesinde okunduğu için 42 uzunluğunda bu array.
                                uint8_t payload[42];
                                read_file(infile, payload);
                                read_file(infile, CK_A);
                                read_file(infile, CK_B);

                                bool check_bool = sbasHelperFunctions::create_checksum_data(classId,msgId,length,gnssId,svId,payload,CK_A,CK_B);

                                if (check_bool) {
                                    reserved0   = payload[0];
                                    freqId      = payload[1];
                                    numWords    = payload[2];
                                    chn         = payload[3];
                                    version     = payload[4];
                                    reserved1   = payload[5];

                                    /// payload içerisinde yer alan wordlerin doğru LSB MSB sırasında birlştirildiği kısım.
                                    /// ubx datasında ters sıra ile geliyor word içersindeki bytelar [LSB ... ... MSB]
                                    for (int i = 0; i < 9; i++) {
                                        /// payload içerisindeki index
                                        int idx = (i + 1) * 4 + 2;
                                        sbasHelperFunctions::uint32_birlestir(payload, idx, dwrd[i]);
                                    }

                                    navEng.yakala_sbas_nav_data(dwrd,svId);
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    std::cout << "Hello, World!" << std::endl;
    return 0;
}
