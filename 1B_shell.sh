#!/bin/bash

opt=1

while [ "$opt" -lt 6 ]; do
  echo -e "\n Choose one of the following:"
  echo "1. Create a New Address Book"
  echo "2. View Records"
  echo "3. Insert New Record"
  echo "4. Delete a Record"
  echo "5. Modify a Record"
  echo "6. Exit"
  read -p "Enter your choice: " opt

  case $opt in
    1) 
      # Create a new address book
      read -p "Enter filename: " fileName
      if [ -e "$fileName" ]; then
        rm "$fileName"  # Remove the file if it already exists
      fi
      echo -e "NAME\tNUMBER\tADDRESS" >> "$fileName"
      
      while true; do
        read -p "Enter Name: " name
        read -p "Enter Phone Number of $name: " number
        read -p "Enter Address of $name: " address
        echo -e "$name\t$number\t$address" >> "$fileName"
        read -p "Enter 0 to stop, 1 to add another entry: " cont
        if [ "$cont" -eq 0 ]; then
          break
        fi
      done
      ;;
    
    2) 
      # View all records
      if [ -e "$fileName" ]; then
        cat "$fileName"
      else
        echo "No address book found. Please create one first."
      fi
      ;;
    
    3)
      # Insert a new record
      if [ -e "$fileName" ]; then
        read -p "Enter Name: " name
        read -p "Enter Phone Number of $name: " number
        read -p "Enter Address of $name: " address
        echo -e "$name\t$number\t$address" >> "$fileName"
      else
        echo "No address book found. Please create one first."
      fi
      ;;
    
    4)
      # Delete a record
      if [ -e "$fileName" ]; then
        read -p "Enter Name or Phone Number to delete: " pattern
        grep -v "$pattern" "$fileName" > temp && mv temp "$fileName"
      else
        echo "No address book found. Please create one first."
      fi
      ;;
    
    5)
      # Modify a record
      if [ -e "$fileName" ]; then
        read -p "Enter Name or Phone Number to modify: " pattern
        grep -v "$pattern" "$fileName" > temp && mv temp "$fileName"
        read -p "Enter New Name: " name
        read -p "Enter New Phone Number of $name: " number
        read -p "Enter New Address of $name: " address
        echo -e "$name\t$number\t$address" >> "$fileName"
      else
        echo "No address book found. Please create one first."
      fi
      ;;
    
    6)
      # Exit the program
      echo "Exiting..."
      exit 0
      ;;
    
    *)
      echo "Invalid option. Please try again."
      ;;
  esac
done

