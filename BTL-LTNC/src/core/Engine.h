#ifndef ENGINE_H
#define ENGINE_H


class Engine
{
    public:
        static Engine* GetInstance() {
        if (s_Instance == nullptr) {
            s_Instance = new Engine();
        }
        return s_Instance;

        bool Init();
        bool Clean();
        void Quit();

        void Update();
        void Render();
        void Events();

        inline bool Isrunning() { return m_Isrunning; }

    protected:

    private:
        Engine();
        bool m_Isrunning;
        static Engine* s_Instance;

};

#endif // ENGINE_H
