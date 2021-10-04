from consolemenu import *
from consolemenu.items import *
import psutil
import os
import random
import json
import xml.etree.ElementTree as ET
import zipfile


def print_disk_info():
  disk_info = []

  for part in psutil.disk_partitions(all=False):
    if os.name == 'nt':
      if 'cdrom' in part.opts or part.fstype == '':
        continue

    usage = psutil.disk_usage(part.mountpoint)

    print("device:", part.device)
    print("total:", usage.total)
    print("used:", usage.used)
    print("free:", usage.free)
    print("percent:", usage.percent)
    print("fstype:", part.fstype)
    print("mountpoint:", part.mountpoint)
    print()

  input()

def create_file():
  f = open(input("Enter filename: "), "w+")
  f.close()

def write_to_file():
  f = open(input("Enter filename: "), "w+")
  f.write(input("Enter text: "))
  f.close()

def read_all_file():
  f = open(input("Enter filename: "), "r")
  print(f.read())
  f.close()
  input()

def delete_file():
  os.remove(input("Enter filename: "))


def create_text_file_menu():
  text_file_menu = ConsoleMenu("Security soft", "Text file")

  create_file_function_item = FunctionItem("Create file", create_file)
  write_text_to_file_function_item = FunctionItem("Write text", write_to_file)
  read_text_from_file_function_item = FunctionItem("Read text", read_all_file)
  delete_file_function_item = FunctionItem("Delete file", delete_file)

  text_file_menu.append_item(create_file_function_item)
  text_file_menu.append_item(write_text_to_file_function_item)
  text_file_menu.append_item(read_text_from_file_function_item)
  text_file_menu.append_item(delete_file_function_item)

  return text_file_menu


class some_struct():
  def __init__(self, id, name, some_doubles):
    self.id = id
    self.name = name
    self.some_doubles = some_doubles

def get_some_struct():
  id = int(input("id = "))
  name = input("name = ")
  some_doubles = []
  for i in range(0, 5):
    some_doubles.append(random.random())

  return some_struct(id, name, some_doubles)


def write_json_obj_to_file():
  ss = get_some_struct()

  f = open(input("Enter filename: "), "w+")  
  f.write(json.dumps(ss.__dict__))
  f.close()

def create_json_file_menu():
  json_file_menu = ConsoleMenu("Security soft", "Json file")

  create_file_function_item = FunctionItem("Create file", create_file)
  write_obj_to_file_function_item = FunctionItem("Write json object", write_json_obj_to_file)
  read_text_from_file_function_item = FunctionItem("Read text", read_all_file)
  delete_file_function_item = FunctionItem("Delete file", delete_file)

  json_file_menu.append_item(create_file_function_item)
  json_file_menu.append_item(write_obj_to_file_function_item)
  json_file_menu.append_item(read_text_from_file_function_item)
  json_file_menu.append_item(delete_file_function_item)

  return json_file_menu


def write_xml_obj_to_file():
  ss = get_some_struct()

  data = ET.Element("some_struct")

  id_element = ET.SubElement(data, "id")
  id_element.text = str(ss.id)

  name_element = ET.SubElement(data, "name")
  name_element.text = ss.name

  some_doubles_element = ET.SubElement(data, "some_doubles")
  for some_double in ss.some_doubles:
    some_double_element = ET.SubElement(some_doubles_element, "some_double")
    some_double_element.text = str(some_double)

  f = open(input("Enter filename: "), "w+")  
  f.write(ET.tostring(data).decode())
  f.close()

def create_xml_file_menu():
  xml_file_menu = ConsoleMenu("Security soft", "Xml file")

  create_file_function_item = FunctionItem("Create file", create_file)
  write_obj_to_file_function_item = FunctionItem("Write xml object", write_xml_obj_to_file)
  read_text_from_file_function_item = FunctionItem("Read text", read_all_file)
  delete_file_function_item = FunctionItem("Delete file", delete_file)

  xml_file_menu.append_item(create_file_function_item)
  xml_file_menu.append_item(write_obj_to_file_function_item)
  xml_file_menu.append_item(read_text_from_file_function_item)
  xml_file_menu.append_item(delete_file_function_item)

  return xml_file_menu


def create_zip_archive():  
  f = zipfile.ZipFile(input("Enter filename: "), "w")
  f.close()

def add_file_to_zip():
  f = zipfile.ZipFile(input("Enter archive name: "), "a")
  path_to_file = input("Enter filename: ")
  f.write(path_to_file, os.path.basename(path_to_file))
  f.close()

def get_file_from_zip():
  archive = zipfile.ZipFile(input("Enter archive name: "), "r")

  filename = input("Enter filename: ")
  data = archive.read(filename)
  archive.close()
    
  f = open(filename, "w+b")
  f.write(data)
  f.close()

  print("size:", os.path.getsize(filename))
  print("modify timestamp:", os.path.getmtime(filename))
  input()

def create_zip_file_menu():
  zip_file_menu = ConsoleMenu("Security soft", "Zip file")
  
  create_file_function_item = FunctionItem("Create zip archive", create_zip_archive)
  add_file_to_zip_function_item = FunctionItem("Add file to zip archive", add_file_to_zip)
  get_file_from_zip_function_item = FunctionItem("Get file from zip archive", get_file_from_zip)
  delete_file_function_item = FunctionItem("Delete zip archive", delete_file)

  zip_file_menu.append_item(create_file_function_item)
  zip_file_menu.append_item(add_file_to_zip_function_item)
  zip_file_menu.append_item(get_file_from_zip_function_item)
  zip_file_menu.append_item(delete_file_function_item)

  return zip_file_menu


def create_menu():
  menu = ConsoleMenu("Security soft", "Lab2")

  menu.append_item(FunctionItem("Get logic disks info", print_disk_info))
  menu.append_item(SubmenuItem("Text file", create_text_file_menu()))
  menu.append_item(SubmenuItem("Json file", create_json_file_menu()))
  menu.append_item(SubmenuItem("Xml file", create_xml_file_menu()))
  menu.append_item(SubmenuItem("Zip file", create_zip_file_menu()))

  return menu


def main():
  menu = create_menu()
  menu.show()

if __name__ == "__main__":
  main()