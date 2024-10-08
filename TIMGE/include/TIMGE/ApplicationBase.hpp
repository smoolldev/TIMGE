#ifndef TIMGE_APPLICATIONBASE_HPP
#define TIMGE_APPLICATIONBASE_HPP

namespace TIMGE
{
    class ApplicationBase
    {
        public:
            explicit ApplicationBase();
            virtual ~ApplicationBase() = 0;

            virtual void Run() = 0;
            virtual void Update() = 0;
            virtual void Render() = 0;
    };
}

#endif // TIMGE_APPLICATIONBASE_HPP
