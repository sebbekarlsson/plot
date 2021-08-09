#ifndef EQ_GUI_SHADER_H
#define EQ_GUI_SHADER_H

class Shader {
  public:
    Shader(int type, char* source);

    static Shader* from_file(int type, const char* filepath);

    void compile();

    void load();

    void release();

    unsigned int get_id();

  private:
    char* source;
    unsigned int type;
    unsigned int id;
};
#endif
