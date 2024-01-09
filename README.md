# Project Tiny Shell - Trần Huy Hoàng 20210386 - HUST

<a name="Giới-thiệu-về-Tiny-Shell"></a>
## 1. Giới thiệu về Tiny Shell

+ Tiny Shell là một giao diện dòng lệnh (command-line interface) giúp người dùng tương tác với hệ điều hành Linux bằng cách nhập lệnh và nhận kết quả trả về.
Tiny Shell là một phiên bản đơn giản của Shell trong hệ điều hành Linux.
+ Mục đích phát triển Tiny Shell là để nghiên cứu cách quản lý tiến trình trong Linux cũng như hiểu cách cài đặt và cách thức Shell làm việc.
+ Dưới đây là các nội dung chính của Project Tiny Shell:
1. [Giới thiệu về Tiny Shell](#Giới-thiệu-về-Tiny-Shell)
2. [Chức năng quản lý tiến trình](#Chuc-nang-quan-ly-tien-trinh)
   + 2.1. [Thực hiện tiến trình ở chế độ foreground, background](#Thuc-hien-tien-trinh-o-che-do-foreground-background)
   + 2.2. [Hiển thị danh sách các tiến trình](#Hien-thi-danh-sach-cac-tien-trinh)
   + 2.3. [Kill một hoặc tất cả background process](#Kill-background-process)
   + 2.4. [Stop và Resume một background process](#Stop-Resume-background-process)
   + 2.5. [Hủy bỏ foreground process bằng tín hiệu ngắt (Ctrl+C)](#Huy-bo-foreground-process)
3. [Giới thiệu các chức năng khác](#Gioi-thieu-cac-chuc-nang-khac)
   + 3.1. [Chức năng của lệnh help](#Chuc-nang-cua-lenh-help)
   + 3.2. [Chức năng của lệnh dir](#Chuc-nang-cua-lenh-dir)
   + 3.3. [Chức năng của lệnh clear và exit](#Chuc-nang-cua-lenh-clear-exit)
   + 3.4. [Chức năng của lệnh date và time](#Chuc-nang-cua-lenh-date-time)
   + 3.5. [Chức năng của lệnh cd](#Chuc-nang-cua-lenh-cd)
   + 3.6. [Chức năng của lệnh path và addpath](#Chuc-nang-cua-lenh-path-addpath)
   + 3.7. [Chức năng của lệnh exec](#Chuc-nang-cua-lenh-exec)

<a name="Chuc-nang-quan-ly-tien-trinh"></a>
## 2. Chức năng quản lý tiến trình
<a name="Thuc-hien-tien-trinh-o-che-do-foreground-background"></a>
### 2.1. Thực hiện tiến trình ở chế độ foreground, background
+ Thực hiện tiến trình ở chế độ **foreground**, ta dùng câu lệnh:
``` 
[path] fg
```
Trong đó [path] là đường dẫn đến file thực thi của tiến trình cần chạy. Ví dụ: 
``` 
./Countdown fg
```
+ Thực hiện tiến trình ở chế độ **background**, ta dùng câu lệnh:
``` 
[path] bg
```
Trong đó [path] là đường dẫn đến file thực thi của tiến trình cần chạy. Ví dụ: 
``` 
./Countdown bg
```
<a name="Hien-thi-danh-sach-cac-tien-trinh"></a>
### 2.2. Hiển thị danh sách các tiến trình
Để hiển thị danh sách các tiến trình, ta dùng câu lệnh: 
``` 
list
```
<a name="Kill-background-process"></a>
### 2.3. Kill một hoặc tất cả background process
+ Để kill một background process, ta dùng lệnh:
``` 
kill [id]
```
Trong đó [id] là ID của tiến trình cần kill. Ví dụ:
``` 
kill 2
```
+ Để kill tất cả background process, ta dùng lệnh:
``` 
killa
```
<a name="Stop-Resume-background-process"></a>
### 2.4. Stop và Resume một background process
+ Để stop một background process đang chạy, ta dùng lệnh:
``` 
stop [id]
```
Trong đó [id] là ID của tiến trình cần stop. Ví dụ:
``` 
stop 2
```
+ Để resume một background process đang dừng (stop), ta dùng lệnh:
``` 
resume [id]
```
Trong đó [id] là ID của tiến trình cần resume. Ví dụ:
``` 
resume 2
```
<a name="Huy-bo-foreground-process"></a>
### 2.5. Hủy bỏ foreground process bằng tín hiệu ngắt (Ctrl+C)
Để hủy bỏ foreground process đang chạy ta dùng tổ hợp phím **CTRL + C**

<a name="Gioi-thieu-cac-chuc-nang-khac"></a>
## 3. Giới thiệu các chức năng khác
<a name="Chuc-nang-cua-lenh-help"></a>
### 3.1. Chức năng của lệnh help
Để hiện thị danh sách thông tin của tất cả các câu lệnh, ta dùng lệnh:
``` 
help
```
<a name="Chuc-nang-cua-lenh-dir"></a>
### 3.2 Chức năng của lệnh dir
Để liệt kê các tệp và thư mục con ở trong thư mục làm việc hiện tại, ta dùng lệnh:
``` 
dir 
```
<a name="Chuc-nang-cua-lenh-clear-exit"></a>
### 3.3 Chức năng của lệnh clear và exit
+ Để xóa toàn bộ nội dung trên màn hình của Tiny Shell, ta dùng lệnh:
``` 
clear
```
+ Để thoát khỏi Tiny Shell, ta dùng lệnh:
``` 
exit
```
<a name="Chuc-nang-cua-lenh-date-time"></a>
### 3.4. Chức năng của lệnh date và time
+ Để hiển thị ngày hiện tại, ta dùng lệnh:
``` 
date
```
+ Để hiển thị giờ hiện tại, ta dùng lệnh:
``` 
time
```
<a name="Chuc-nang-cua-lenh-cd"></a>
### 3.5. Chức năng của lệnh cd
Để thay đổi thư mục làm việc hiện tại, ta dùng lệnh: 
``` 
cd [path]
```
Trong đó [path] là đường dẫn đến thư mục mới. Ví dụ: 
``` 
cd /home/hoangtran/Downloads
```
<a name="Chuc-nang-cua-lenh-path-addpath"></a>
### 3.6. Chức năng của lệnh path và addpath
Để in ra giá trị của biến môi trường PATH, ta dùng lệnh:
``` 
path
```
Để thêm đường dẫn vào biến môi trường PATH, ta dùng lệnh:
``` 
addpath [path]
```
Trong đó [path] là đường dẫn tuyệt đối cần thêm vào biến PATH. Ví dụ
``` 
addpath /home/hoangtran/newPath
```
<a name="Chuc-nang-cua-lenh-exec"></a>
### 3.7. Chức năng của lệnh exec
Để thực thi file .sh (Shell script), ta dùng lệnh:
``` 
exec [path]
```
Trong đó [path] là đường dẫn đến file .sh. Ví dụ:
``` 
exec ./script.sh
```
