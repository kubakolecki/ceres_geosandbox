import numpy as np
import os as os
from geometry import Point2d

path_directory_data = '../../sandbox_datasets/02'
path_file_coordinates = os.path.join(path_directory_data,'coordinates_initial.txt')
path_file_graph_distances = os.path.join(path_directory_data,'distances_graph.txt')
path_file_graph_angles = os.path.join(path_directory_data,'angles_graph.txt')
path_file_graph_gps = os.path.join(path_directory_data,'gnss_graph.txt')
noise_disnce = 0.02
noise_angle = 0.0030*np.pi/200.0
noise_gps = 0.015


coordinates_table = np.loadtxt(path_file_coordinates, skiprows=1, delimiter=',', dtype='str')
graph_distances = np.loadtxt(path_file_graph_distances, skiprows=1, delimiter=',', dtype='str')
graph_angles = np.loadtxt(path_file_graph_angles, skiprows=1, delimiter=',', dtype='str')
graph_gps = np.loadtxt(path_file_graph_gps, skiprows=1, delimiter=',', dtype='str')


coordinates_dict = {}

num_of_points = coordinates_table.shape[0]
num_of_angles = graph_angles.shape[0]
num_of_distances = graph_distances.shape[0]
num_of_gps = graph_gps.shape[0]

for i in range(num_of_points):
    id = coordinates_table[i,0]
    e = float(coordinates_table[i,1])
    n = float(coordinates_table[i,2])
    coordinates_dict[id] = Point2d(id,e,n)

path_file_output_distances = os.path.join(path_directory_data,'distances_observations.txt')
path_file_output_angles = os.path.join(path_directory_data,'angles_observations.txt')
path_file_output_gps = os.path.join(path_directory_data,'gnss_observations.txt')
path_file_output_coordinates_final = os.path.join(path_directory_data,'coordinates.txt')

with open(path_file_output_distances,'w') as f_dist:
    f_dist.write('id_from,id_to,distance,noise\n')
    for i in range(num_of_distances):
        id_from = graph_distances[i,0]
        id_to = graph_distances[i,1]
        point_from = coordinates_dict[id_from]
        point_to = coordinates_dict[id_to]
        distance = np.sqrt((point_from.e - point_to.e)**2 + (point_from.n - point_to.n)**2)
        noise = np.random.normal(0,noise_disnce)
        #noise = 0
        distance_noisy = distance + noise
        f_dist.write(f'{id_from},{id_to},{distance_noisy},{noise_disnce}\n')

with open(path_file_output_angles,'w') as f_ang:
    f_ang.write('id_center,id_left, id_right, angle,noise\n')
    for i in range(num_of_angles):
        id_center = graph_angles[i,0]
        id_left= graph_angles[i,1]
        id_right = graph_angles[i,2]
        point_center = coordinates_dict[id_center]
        point_left = coordinates_dict[id_left]
        point_right = coordinates_dict[id_right]
        de_left = point_left.e - point_center.e
        dn_left = point_left.n - point_center.n
        de_right = point_right.e - point_center.e
        dn_right = point_right.n - point_center.n
        #angle = np.arctan(de_right/dn_right) - np.arctan(de_left/dn_left)
        angle = np.arctan2(de_right,dn_right) - np.arctan2(de_left,dn_left)
        #if angle < 0:
        #    angle += 2.0*np.pi
        noise = np.random.normal(0,noise_angle)
        #noise = 0
        angle_noisy = angle + noise
        f_ang.write(f'{id_center},{id_left},{id_right},{angle_noisy},{noise_angle}\n')

with open(path_file_output_gps,'w') as f_gps:
    f_gps.write('id,easting,northing,noise\n')
    for i in range(num_of_gps):
        id = graph_gps[i]
        point = coordinates_dict[id]
        noise_e = np.random.normal(0,noise_gps)
        noise_n = np.random.normal(0,noise_gps)
        #noise_e = 0
        #noise_n = 0
        e_noisy = point.e + noise_e
        n_noisy = point.n + noise_n
        f_gps.write(f'{id},{e_noisy},{n_noisy},{noise_gps}\n')

with open(path_file_output_coordinates_final,'w') as f_coor:
    f_coor.write('id,easting,northing\n')
    for i in range(num_of_points):
        id = coordinates_table[i,0]
        point = coordinates_dict[id]
        point.e = np.round(point.e,0) + np.random.normal(0,0.1) # add small noise to avoid same coordinat
        point.n = np.round(point.n,0) + np.random.normal(0,0.1)
        f_coor.write(f'{id},{point.e},{point.n}\n') 
