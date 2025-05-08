# 🚀 Laboratorio 13-1: Conexión de C++/CLI con SQL Server 🎯

![SQL Server](https://img.shields.io/badge/SQL%20Server-007ACC?style=flat-square&logo=microsoft-sql-server) ![C++](https://img.shields.io/badge/C%2B%2B-00599C?style=flat-square&logo=c%2B%2B)

## 📝 Descripción
Este laboratorio muestra cómo crear una aplicación de consola en C++/CLI que se conecta a una base de datos SQL Server, ejecuta una consulta y muestra los resultados por pantalla.

## 🎯 Objetivos
- 🎈 Configurar un proyecto C++/CLI con soporte CLR en Visual Studio.  
- 🏗️ Crear una base de datos y tabla en SQL Server.  
- 🧩 Ejecutar consultas y leer resultados con `SqlConnection`, `SqlCommand` y `SqlDataReader`.

## ✅ Requisitos
- 📀 Windows 10/11  
- 🗄️ SQL Server (p. ej. SQL Server Express)  
- 🛠️ Visual Studio con soporte de **/clr**  
- 🔑 Permisos para crear bases y tablas

---

## 📂 Preparación de la base de datos

En SSMS, ejecuta:

```sql
-- Crear la base de datos
CREATE DATABASE Escuela;
GO
USE Escuela;
GO

-- Crear la tabla Estudiantes
CREATE TABLE Estudiantes (
  Id     INT IDENTITY(1,1) PRIMARY KEY,
  Nombre NVARCHAR(100),
  Edad   INT
);
GO

-- Insertar datos de prueba
INSERT INTO Estudiantes (Nombre, Edad)
VALUES
  ('Ana García',    20),
  ('Carlos Pérez',  22),
  ('Lucía Mendoza', 21);
GO
```

---

## ⚙️ Configuración del proyecto

1. **Nuevo proyecto** →  
   - Tipo: **CLR Console Application**  
   - Lenguaje: **Visual C++**  
   - Nombre: `ConexionBaseDatosSQL`  
2. **Propiedades** ▶ **C/C++** ▶ **Common Language Runtime Support (/clr)**  
3. **References** ▶ **Add Reference…** ▶  
   - ☑️ System  
   - ☑️ System.Data  

---

## 💻 Implementación del código

Reemplaza `main.cpp` con:

```cpp
#include "pch.h"              // o "stdafx.h"
#using <System.dll>
#using <System.Data.dll>

using namespace System;
using namespace System::Data;
using namespace System::Data::SqlClient;

int main(array<String^>^ args)
{
    // 🔌 Ajusta tu instancia de SQL Server
    String^ cadenaConexion =
        "Server=localhost\\SQLEXPRESS;" 
        "Database=Escuela;"
        "Integrated Security=True;";

    auto conexion = gcnew SqlConnection(cadenaConexion);
    try
    {
        conexion->Open();
        Console::WriteLine("🌐 Conexión exitosa!");

        String^ sql = "SELECT Id, Nombre, Edad FROM Estudiantes;";
        auto cmd = gcnew SqlCommand(sql, conexion);
        auto lector = cmd->ExecuteReader();

        while (lector->Read())
        {
            int id = lector->GetInt32(0);
            String^ nombre = lector->GetString(1);
            int edad = lector->GetInt32(2);

            Console::WriteLine($"➡️ ID: {id}, Nombre: {nombre}, Edad: {edad}");
        }

        lector->Close();
        delete lector;
        delete cmd;
        conexion->Close();
        delete conexion;
    }
    catch (SqlException^ ex)
    {
        Console::WriteLine($"❌ Error de SQL Server: {ex->Message}");
    }
    catch (Exception^ ex)
    {
        Console::WriteLine($"⚠️ Error inesperado: {ex->Message}");
    }

    Console::WriteLine("\n✅ Presiona Enter para salir...");
    Console::ReadLine();
    return 0;
}
```

---

## ▶️ Compilación y ejecución

1. **Build** ▶ **Rebuild Solution**  
2. **Debug** ▶ **Start Without Debugging** (Ctrl+F5)  
3. Deberías ver:

```
🌐 Conexión exitosa!
➡️ ID: 1, Nombre: Ana García, Edad: 20
➡️ ID: 2, Nombre: Carlos Pérez, Edad: 22
➡️ ID: 3, Nombre: Lucía Mendoza, Edad: 21

✅ Presiona Enter para salir...
```

---

## 🎉 Resultado esperado
- Conexión sin errores.  
- Listado de registros de `Estudiantes`.

---

## 🔧 Solución de problemas
- **🔑 Autenticación**: revisa `Integrated Security` o usa `User Id`/`Password`.  
- **📡 Instancia**: comprueba el `Server=…`.  
- **🛠️ CLR**: activa `/clr` en Propiedades ▶ C/C++.

---

