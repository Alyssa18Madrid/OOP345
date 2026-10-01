/***********************************************************************
Name: Alyssa Madrid
Seneca Email: amadrid1@myseneca.ca
Seneca Student ID: 103610259
Date Completed: October 1, 2026

I received assistance from AI while working on this
assignment. The assistance included reviewing the assignment
requirements and providing guidance/examples for the implementation of
Settings, Event, Logger, TimeMonitor, and Dictionary.

I reviewed and adapted the code for this assignment and tested it
against the provided tester.
***********************************************************************/
#include <iostream>
#include <fstream>
#include <string>
#include "dictionary.h"
#include "settings.h"

namespace seneca
{
    Dictionary::Dictionary(const char* filename)
    {
        std::ifstream file(filename);
        std::string line;

        if (file)
        {
            // Count how many records are in the file
            while (std::getline(file, line))
            {
                m_size++;
            }

            // Allocate exactly enough memory for all records
            if (m_size > 0)
            {
                m_words = new Word[m_size];

                // Go back to the beginning of the file
                file.clear();
                file.seekg(0);

                size_t i = 0;

                while (std::getline(file, line))
                {
                    size_t firstComma = line.find(',');
                    size_t secondComma = line.find(',', firstComma + 1);

                    // Get the word
                    m_words[i].m_word =
                        line.substr(0, firstComma);

                    // Get the part of speech
                    std::string pos =
                        line.substr(firstComma + 1,
                            secondComma - firstComma - 1);

                    // Get the definition
                    m_words[i].m_definition =
                        line.substr(secondComma + 1);

                    // Convert the part of speech
                    if (pos == "n." || pos == "n. pl.")
                    {
                        m_words[i].m_pos = PartOfSpeech::Noun;
                    }
                    else if (pos == "adv.")
                    {
                        m_words[i].m_pos = PartOfSpeech::Adverb;
                    }
                    else if (pos == "a.")
                    {
                        m_words[i].m_pos = PartOfSpeech::Adjective;
                    }
                    else if (pos == "v." ||
                        pos == "v. i." ||
                        pos == "v. t." ||
                        pos == "v. t. & i.")
                    {
                        m_words[i].m_pos = PartOfSpeech::Verb;
                    }
                    else if (pos == "prep.")
                    {
                        m_words[i].m_pos = PartOfSpeech::Preposition;
                    }
                    else if (pos == "pron.")
                    {
                        m_words[i].m_pos = PartOfSpeech::Pronoun;
                    }
                    else if (pos == "conj.")
                    {
                        m_words[i].m_pos = PartOfSpeech::Conjunction;
                    }
                    else if (pos == "interj.")
                    {
                        m_words[i].m_pos = PartOfSpeech::Interjection;
                    }
                    else
                    {
                        m_words[i].m_pos = PartOfSpeech::Unknown;
                    }

                    i++;
                }
            }
        }
    }


    // Copy Constructor
    Dictionary::Dictionary(const Dictionary& other)
    {
        m_size = other.m_size;

        if (m_size > 0)
        {
            m_words = new Word[m_size];

            for (size_t i = 0; i < m_size; i++)
            {
                m_words[i] = other.m_words[i];
            }
        }
    }


    // Copy Assignment Operator
    Dictionary& Dictionary::operator=(const Dictionary& other)
    {
        if (this != &other)
        {
            delete[] m_words;

            m_size = other.m_size;
            m_words = nullptr;

            if (m_size > 0)
            {
                m_words = new Word[m_size];

                for (size_t i = 0; i < m_size; i++)
                {
                    m_words[i] = other.m_words[i];
                }
            }
        }

        return *this;
    }


    // Move Constructor
    Dictionary::Dictionary(Dictionary&& other)
    {
        m_words = other.m_words;
        m_size = other.m_size;

        other.m_words = nullptr;
        other.m_size = 0;
    }


    // Move Assignment Operator
    Dictionary& Dictionary::operator=(Dictionary&& other)
    {
        if (this != &other)
        {
            delete[] m_words;

            m_words = other.m_words;
            m_size = other.m_size;

            other.m_words = nullptr;
            other.m_size = 0;
        }

        return *this;
    }


    // Destructor
    Dictionary::~Dictionary()
    {
        delete[] m_words;
    }


    // Search for a word
    void Dictionary::searchWord(const char* word)
    {
        bool found = false;

        for (size_t i = 0; i < m_size; i++)
        {
            if (m_words[i].m_word == word)
            {
                // Print the word only for the first definition
                if (found == false)
                {
                    std::cout << m_words[i].m_word;
                    found = true;
                }
                else
                {
                    // Print spaces instead of the word
                    for (size_t j = 0;
                        j < m_words[i].m_word.length();
                        j++)
                    {
                        std::cout << ' ';
                    }
                }

                std::cout << " - ";

                // Print part of speech only when verbose is enabled
                // and the part of speech is known
                if (g_settings.m_verbose == true &&
                    m_words[i].m_pos != PartOfSpeech::Unknown)
                {
                    std::cout << "(";

                    switch (m_words[i].m_pos)
                    {
                    case PartOfSpeech::Noun:
                        std::cout << "noun";
                        break;

                    case PartOfSpeech::Pronoun:
                        std::cout << "pronoun";
                        break;

                    case PartOfSpeech::Adjective:
                        std::cout << "adjective";
                        break;

                    case PartOfSpeech::Adverb:
                        std::cout << "adverb";
                        break;

                    case PartOfSpeech::Verb:
                        std::cout << "verb";
                        break;

                    case PartOfSpeech::Preposition:
                        std::cout << "preposition";
                        break;

                    case PartOfSpeech::Conjunction:
                        std::cout << "conjunction";
                        break;

                    case PartOfSpeech::Interjection:
                        std::cout << "interjection";
                        break;

                    default:
                        break;
                    }

                    std::cout << ") ";
                }

                // Print the definition
                std::cout << m_words[i].m_definition
                    << std::endl;

                // Stop after the first definition if required
                if (g_settings.m_show_all == false)
                {
                    return;
                }
            }
        }

        // The word was not found
        if (found == false)
        {
            std::cout << "Word '" << word
                << "' was not found in the dictionary."
                << std::endl;
        }
    }
}