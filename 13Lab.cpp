// 13Lab.cpp
#include "pch.h"
#using <System.dll>

using namespace System;
using namespace MySql::Data::MySqlClient;

int main(array<String^>^ args)
{
    String^ cadenaConexion =
        "server=127.0.0.1;"
        "port=3306;"
        "user id=root;"
        "database=Escuela;"
        "Character Set=utf8mb4;";


    auto conexion = gcnew MySqlConnection(cadenaConexion);
    try
    {
        conexion->Open();
        Console::WriteLine("Conexión exitosa a la base de datos.");

        String^ sql = "SELECT * FROM Estudiantes";
        auto cmd = gcnew MySqlCommand(sql, conexion);
        auto lector = cmd->ExecuteReader();

        // Recorrer filas
        while (lector->Read())
        {
            Console::WriteLine("ID: {0}, Nombre: {1}, Edad: {2}",
                lector["Id"], lector["Nombre"], lector["Edad"]);
        }


        // Cerrar y liberar
        lector->Close();
        delete lector;
        delete cmd;
        conexion->Close();
        delete conexion;
    }
    catch (MySqlException^ mex)
    {
        Console::WriteLine("Error de MySQL: {0}", mex->Message);

    }
    catch (Exception^ ex)
    {
        Console::WriteLine("Error inesperado: {0}", ex->Message);
    }

    Console::Write("\nPresiona Enter para salir...");
    Console::ReadLine();
    return 0;
}
