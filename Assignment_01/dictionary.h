#ifndef SENECA_DICTIONARY_H
#define SENECA_DICTIONARY_H

#include <string>

namespace seneca
{
    enum class PartOfSpeech
    {
        Unknown,
        Noun,
        Pronoun,
        Adjective,
        Adverb,
        Verb,
        Preposition,
        Conjunction,
        Interjection,
    };

    struct Word
    {
        std::string m_word{};
        std::string m_definition{};
        PartOfSpeech m_pos = PartOfSpeech::Unknown;
    };

    class Dictionary
    {
        Word* m_words{ nullptr };
        size_t m_size{ 0 };

    public:
        Dictionary() = default;
        Dictionary(const char* filename);

        Dictionary(const Dictionary& other);
        Dictionary& operator=(const Dictionary& other);

        Dictionary(Dictionary&& other);
        Dictionary& operator=(Dictionary&& other);

        ~Dictionary();

        void searchWord(const char* word);
    };
}

#endif